import * as React from 'react';
import Link from './Link';
import Paper from '@mui/material/Paper';
import BottomNavigation from '@mui/material/BottomNavigation';
import BottomNavigationAction from '@mui/material/BottomNavigationAction';
import BoltIcon from '@mui/icons-material/Bolt';
import HomeIcon from '@mui/icons-material/Home';
import FavoriteIcon from '@mui/icons-material/Favorite';
import QuestionMarkIcon from '@mui/icons-material/QuestionMark';


export default function LabelBottomNavigation() {
  const [value, setValue] = React.useState('home');

  const handleChange = (event: React.SyntheticEvent, newValue: string) => {
    setValue(newValue);
  };

  return (
    <Paper sx={{ position: 'fixed', bottom: 0, left: 0, right: 0}} elevation={3}>
      <BottomNavigation sx={{ width: '100vw' }} value={value} onChange={handleChange}>
        <BottomNavigationAction
          component={Link}
          label="Home"
          value="home"
          icon={<HomeIcon />}
          href="/"
        />
        <BottomNavigationAction
          component={Link}
          label="Heart Rate"
          value="heart-rate"
          icon={<FavoriteIcon />}
          href="/heartRate"
        />
        <BottomNavigationAction
          component={Link}
          label="Activity"
          value="bolt"
          icon={<BoltIcon />}
          href="/movement"
        />
        <BottomNavigationAction
          component={Link}
          label="About"
          value="about"
          icon={<QuestionMarkIcon />}
          href="/about"
        />
      </BottomNavigation>
    </Paper>
  );
}
