import * as React from 'react';
import Container from '@mui/material/Container';
import Typography from '@mui/material/Typography';
import Box from '@mui/material/Box';
import Link from '../src/Link';

export default function Home() {
  return (
      <Container maxWidth="lg">
        <Box
          sx={{
            my: 4,
            display: 'flex',
            flexDirection: 'column',
            justifyContent: 'normal',
            alignItems: 'normal'
          }}
        >
          <Typography variant="h4" component="h1" gutterBottom>
            General Information
          </Typography>


          <Typography variant="h4" component="h1" gutterBottom>
            Live data
          </Typography>


          <Link href="/about" color="secondary">
            Go to the about page
          </Link>
          
        </Box>
      </Container>
  );
}
