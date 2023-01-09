import Container from '@mui/material/Container';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';
import { NextPageContext } from 'next';

const server = 'http://localhost:3000'

export async function getServerSideProps(context: NextPageContext) {

  let raw_data = await fetch(`${server}/api/heart`);
  let heartRates = await raw_data.json();
  heartRates.reverse();

  return {
    props: {
      heartRates
    }
  };
}

export default function HeartRate(props: any) {
  const heartRates: any[] = props.heartRates;
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
            {heartRates.map((row) => (
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