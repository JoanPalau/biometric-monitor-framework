import * as React from 'react';
import Head from 'next/head';
import { AppProps } from 'next/app';
import { ThemeProvider } from '@mui/material/styles';
import CssBaseline from '@mui/material/CssBaseline';
import { CacheProvider, EmotionCache } from '@emotion/react';
import theme from '../src/theme';
import createEmotionCache from '../src/createEmotionCache';
import MyAppBar from '../src/AppBar';
import LabelBottomNavigation from '../src/BottomNavigation';
const mqtt = require('mqtt')
const client  = mqtt.connect('mqtt://localhost')

const server = 'http://localhost:3000'

client.on('connect', function () {
  client.subscribe('sensor/heart', function (err:any) {
    console.log('OK HEA')
  })
  client.subscribe('sensor/accelerometer', function (err:any) {
    console.log('OK ACC')
  })
})

client.on('message', function (topic:any, message:any) {
  console.log(topic, message.toString())
  if (topic === 'sensor/heart') {
    fetch(
      `${server}/api/heart`,
      {
        method: 'POST',
        body: JSON.stringify({
          heart: message.toString()
        }),
        headers: {
          'Content-type': 'application/json'
        }
      }
    )
  } else {
    let data = message.toString().split(' ');
    if (data.length < 4) {
      return;
    }
    data = data[3];
    fetch(
      `${server}/api/activity`,
      {
        method: 'POST',
        body: JSON.stringify({
          activity: data
        }),
        headers: {
          'Content-type': 'application/json'
        }
      }
    )
  }
  // message is Buffer
  // client.end()
})

// Client-side cache, shared for the whole session of the user in the browser.
const clientSideEmotionCache = createEmotionCache();

interface MyAppProps extends AppProps {
  emotionCache?: EmotionCache;
}

export default function MyApp(props: MyAppProps) {
  const { Component, emotionCache = clientSideEmotionCache, pageProps } = props;
  return (
    <CacheProvider value={emotionCache}>
      <Head>
        <meta name="viewport" content="initial-scale=1, width=device-width" />
      </Head>
      <ThemeProvider theme={theme}>
        {/* CssBaseline kickstart an elegant, consistent, and simple baseline to build upon. */}
        <CssBaseline />
        <MyAppBar />
        <Component {...pageProps}/>
        <LabelBottomNavigation />
      </ThemeProvider>
    </CacheProvider>
  );
}
