import Container from '@mui/material/Container';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import { NextPageContext } from 'next';


function createData(
  timestamp: string,
  activity: string
) {
  return { timestamp, activity };
}

const rows = [
  createData('09/01/2022 - 15:00:00', 'WALK'),
  createData('09/01/2022 - 15:01:00', 'WALK'),
  createData('09/01/2022 - 15:02:00', 'WALK'),
  createData('09/01/2022 - 15:03:00', 'WALK'),
  createData('09/01/2022 - 15:04:00', 'RUN'),
];

const server = 'http://localhost:3000'

export async function getServerSideProps(context: NextPageContext) {

  const raw_data = await fetch(`${server}/api/activity`);

  let activities = await raw_data.json();

  activities = activities.reverse();

  return {
    props: {
      activities
    }
  };
}

export default function HeartRate(props: any) {
  const activities: any[] = props.activities;

  return (
    <Container maxWidth="lg">
      <TableContainer sx={{marginTop: '1rem'}} component={Paper}>
        <Table aria-label="Heart rate table">
          <TableHead>
            <TableRow>
              <TableCell>Timestamp (UTC)</TableCell>
              <TableCell align="right">Activity type</TableCell>
            </TableRow>
          </TableHead>
          <TableBody>
            {activities.map((row) => (
              <TableRow
                key={row.id}
                sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
              >
                <TableCell component="th" scope="row">
                  {row.created_at}
                </TableCell>
                <TableCell align="right">{row.value}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Container>
  );
}