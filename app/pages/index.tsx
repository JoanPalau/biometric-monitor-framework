import { useEffect, useState } from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';

const mqtt = require('mqtt')


const server = 'http://localhost:3000'



export default function Home() {

  const [heartRate, setHeartRate] = useState('--');
  const [activity, setActivity] = useState('No data');

  // useEffect(
  //   () => {
  //     console.log('use Effect!');
  //     const timer = setTimeout(
  //       () => {
  //         console.log('Api heart!');
  //         // let heartData = await fetch(
  //         //   `${server}/api/heart`,
  //         //   {
  //         //     method: 'GET',
  //         //     headers: {
  //         //       'Content-type': 'application/json'
  //         //     }
  //         //   }
  //         // )
  //         console.log('End set timeout');
  //       },
  //       1000
  //     )

  //     return () => clearTimeout(timer);
  //   }
  // );

  useEffect(() => {
    const timer = setTimeout(async () => {
      // setCount('Timeout called!');
      let heartData = await fetch(
        `${server}/api/heart`,
        {
          method: 'GET',
          headers: {
            'Content-type': 'application/json'
          }
        }
        )
      heartData = await heartData.json();
      setHeartRate(heartData[heartData.length - 1].value);

      let activityData = await fetch(
        `${server}/api/activity`,
        {
          method: 'GET',
          headers: {
            'Content-type': 'application/json'
          }
        }
        )
        activityData = await activityData.json();
      setActivity(activityData[activityData.length - 1].value);
    }, 1500);
    return () => clearTimeout(timer);
  });


  return (
    <Container maxWidth="lg">
      <Box
        sx={{
          my: 4,
          display: 'flex',
          flexDirection: 'column',
          justifyContent: 'center',
          alignItems: 'center',
          height: '80vh'
        }}
      >
        <Typography variant="h4" component="h1" gutterBottom>
          Heart Rate
        </Typography>
        <Typography variant="h6" component="h1" gutterBottom>
          {heartRate}
        </Typography>

        <Typography variant="h4" component="h1" gutterBottom>
          Activity
        </Typography>
        <Typography variant="h6" component="h1" gutterBottom>
          {activity}
        </Typography>

      </Box>
    </Container>
  );
}
