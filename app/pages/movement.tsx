import Container from '@mui/material/Container';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';


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

export default function HeartRate() {
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
            {rows.map((row, index) => (
              <TableRow
                key={index}
                sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
              >
                <TableCell component="th" scope="row">
                  {row.timestamp}
                </TableCell>
                <TableCell align="right">{row.activity}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Container>
  );
}