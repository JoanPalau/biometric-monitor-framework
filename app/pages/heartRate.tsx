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
  bpm: number
) {
  return { timestamp, bpm };
}

const rows = [
  createData('09/01/2022 - 15:00:00', 159),
  createData('09/01/2022 - 15:01:00', 237),
  createData('09/01/2022 - 15:02:00', 262),
  createData('09/01/2022 - 15:03:00', 150),
  createData('09/01/2022 - 15:04:00', 356),
];

export default function HeartRate() {
  return (
    <Container maxWidth="lg">
      <TableContainer sx={{marginTop: '1rem'}} component={Paper}>
        <Table aria-label="Heart rate table">
          <TableHead>
            <TableRow>
              <TableCell>Timestamp (UTC)</TableCell>
              <TableCell align="right">Heart rate (BPM)</TableCell>
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
                <TableCell align="right">{row.bpm}</TableCell>
              </TableRow>
            ))}
          </TableBody>
        </Table>
      </TableContainer>
    </Container>
  );
}