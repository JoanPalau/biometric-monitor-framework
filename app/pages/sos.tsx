import Container from '@mui/material/Container';
import Table from '@mui/material/Table';
import TableBody from '@mui/material/TableBody';
import TableCell from '@mui/material/TableCell';
import TableContainer from '@mui/material/TableContainer';
import TableHead from '@mui/material/TableHead';
import TableRow from '@mui/material/TableRow';
import Paper from '@mui/material/Paper';

import { Annotation, ComposableMap, Geographies, Geography, Marker } from "react-simple-maps"

const geoUrl =
    "https://raw.githubusercontent.com/deldersveld/topojson/master/countries/spain/spain-comunidad.json";

import { NextPageContext } from 'next';
import { Stack } from '@mui/material';

const markers = [
    { markerOffset: -15, name: "SOS", coordinates: [0.6149036, 41.6117585] },
];

const server = 'http://localhost:3000'

export async function getServerSideProps(context: NextPageContext) {

    //const raw_data = await fetch(`${server}/api/activity`);

    //let activities = await raw_data.json();

    //activities = activities.reverse();

    const raw_data = await fetch(`${server}/api/alerts`);

    let alerts = await raw_data.json();

    //const activity = activities[0];

    //const date = new Date();
    //const alerts = [{ id: 1, created_at: date.toString(), value: activity.value, user: 'Joan' }]

    return {
        props: {
            alerts
        }
    };
}

export default function Sos(props: any) {
    return (
        <Container>
            <Stack>
                <ComposableMap
                    projection="geoAzimuthalEqualArea"
                    projectionConfig={{
                        center: [177, 140],
                        scale: 3000,
                    }}
                >
                    <Geographies geography={geoUrl}>
                        {({ geographies }) =>
                            geographies.map((geo) => {
                                return (

                                    <Geography key={geo.rsmKey} geography={geo} />
                                )
                            })
                        }
                    </Geographies>
                    {markers.map(({ name, coordinates, markerOffset }) => (
                        <Marker key={name} coordinates={coordinates}>
                            <circle r={10} fill="#F00" stroke="#fff" strokeWidth={2} />
                            <text
                                textAnchor="middle"
                                y={markerOffset}
                                style={{ fontFamily: "system-ui", fill: "red" }}
                            >
                                {name}
                            </text>
                        </Marker>
                    ))
                    }
                </ComposableMap>
                <TableContainer sx={{ marginTop: '1rem' }} component={Paper}>
                    <Table aria-label="Heart rate table">
                        <TableHead>
                            <TableRow>
                                <TableCell>Time (UTC)</TableCell>
                                <TableCell align="right">Activity type</TableCell>
                                <TableCell>User</TableCell>
                            </TableRow>
                        </TableHead>
                        <TableBody>
                            {
                                props.alerts.map(alert => (
                                    <TableRow
                                        key={alert.id}
                                        sx={{ '&:last-child td, &:last-child th': { border: 0 } }}
                                    >
                                        <TableCell component="th" scope="row">
                                            {
                                                alert.created_at
                                            }
                                        </TableCell>
                                        <TableCell align="right">{alert.activity}</TableCell>
                                        <TableCell>{alert.user}</TableCell>
                                    </TableRow>
                                ))
                            }



                        </TableBody>
                    </Table>
                </TableContainer>
            </Stack>
        </Container>

    );
}