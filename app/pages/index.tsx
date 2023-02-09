import { useEffect, useState } from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import Chip from '@mui/material/Chip';
import { Button } from '@mui/material';

import { predict } from '../src/riskPredictor';

import { useRouter } from 'next/router'

const riskValueColorMapper: string[] = [
  'default',
  'success',
  'warning',
  'error'
]

const riskValueLabelMapper = [
  "No risk information",
  "Low",
  "Medium",
  "High"
]

const mqtt = require('mqtt')


const server = 'http://localhost:3000'



export default function Home() {

  let n=0;
  let avgHeartRate = -1;

  const [heartRate, setHeartRate] = useState('--');
  const [activity, setActivity] = useState('No data');
  const [risk, setRisk] = useState(0);

  const router = useRouter();

  /*
  useEffect(()=> {
    setTimeout( () => triggerRiskStatusChange(Math.floor(Math.random() * 4)), 500)
  });
  */

  const triggerRiskStatusChange = (newRisk: number) => {
    if( newRisk !== risk && newRisk === 3) {
      navigator.geolocation.getCurrentPosition(function(position) {
        console.log("Latitude is :", position.coords.latitude);
        console.log("Longitude is :", position.coords.longitude);
      });
    }
    setRisk(newRisk);
  }

  useEffect(() => {
    const timer = setTimeout(async () => {
      // setCount('Timeout called!');
      let heartData:any = await fetch(
        `${server}/api/heart`,
        {
          method: 'GET',
          headers: {
            'Content-type': 'application/json'
          }
        }
        )
      heartData = await heartData.json();
      const new_hr = heartData[heartData.length - 1].value;
      if (avgHeartRate === -1) {
        avgHeartRate = new_hr;
      } else {
        avgHeartRate = (avgHeartRate * n + new_hr) / n+1;
      }
      setHeartRate(new_hr);
      n += 1;

      let activityData:any = await fetch(
        `${server}/api/activity`,
        {
          method: 'GET',
          headers: {
            'Content-type': 'application/json'
          }
        }
        )
      activityData = await activityData.json();
      const new_activity = activityData[activityData.length - 1].value

      console.log(new_activity)
      console.log(new_hr)
      console.log(avgHeartRate)
      console.log(predict(181, new_activity, 181, activityData))
      triggerRiskStatusChange(predict(181, new_activity, 181, activityData))
      setActivity(new_activity);

    }, 1500);
    return () => clearTimeout(timer);
  });

  useEffect(()=> {
    navigator.geolocation.getCurrentPosition(function(position) {
      console.log("Latitude is :", position.coords.latitude);
      console.log("Longitude is :", position.coords.longitude);
    });
  })


  const handleSOSClick = () => {
    router.push('/sos');
  }


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
          <Chip label={riskValueLabelMapper[risk]} color={riskValueColorMapper[risk]}/>
          <br/>
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

          {
            risk === 3 ? 
              <Button 
                sx={{ position: 'fixed', bottom: '15%', width: '80%'}} 
                color="error" 
                variant="contained" 
                size="large"
                onClick={handleSOSClick}
                >
                  SOS
              </Button> : null
          }
          
        </Box>
      </Container>
  );
}
