import { useState } from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';

export default function Home() {

  const [heartRate, setHeartRate] = useState('--');
  const [activity, setActivity] = useState('No data');

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
