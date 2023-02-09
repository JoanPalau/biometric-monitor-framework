import { PrismaClient } from '@prisma/client'
import { NextApiRequest, NextApiResponse } from 'next';
const prisma = new PrismaClient()

export default async function handler(req: NextApiRequest, res: NextApiResponse) {
      const {
          query: { },
          method,
      } = req
    console.log("[LOG] " + method + " with query " + JSON.stringify(req.query) + " and body " + JSON.stringify(req.body));
    if (req.method === 'GET') {
      // Process a GET request
      let x = await prisma.alertsHistory.findMany();
      res.status(200).json(x)
    } else if (req.method === 'POST') {
      // Process a POST request

      console.log(req.body);
      let x = await prisma.alertsHistory.create({
        data: {
          activity: req.body.activity,
          long: req.body.long,
          lat: req.body.lat,
          user: 'Joan'
        }
      })
      res.status(201).end();
    } else if(req.method === 'PATCH') {
        let x = await prisma.alertsHistory.update({
            where: {
                id: req.body.id
            },
            data: {
              ack: true
            }
          })
          res.status(201).end();
    } else {
      // Handle any other HTTP method
      res.status(400).json({ message: 'Bad request' })
    }
}