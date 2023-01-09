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
      let x = await prisma.activityHistory.findMany();
      res.status(200).json(x)
    } else if (req.method === 'POST') {
      // Process a POST request
      let x = await prisma.activityHistory.create({
        data: {
          value: req.body.activity
        }
      })
      res.status(201).end();
    } else {
      // Handle any other HTTP method
      res.status(400).json({ message: 'Bad request' })
    }
}