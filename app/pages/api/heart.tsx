import { PrismaClient } from '@prisma/client'
const prisma = new PrismaClient()

export default async function handler(req, res) {
      const {
          query: { },
          method,
      } = req
    console.log("[LOG] " + method + " with query " + JSON.stringify(req.query) + " and body " + JSON.stringify(req.body));
    if (req.method === 'GET') {
      // Process a GET request
      let x = await prisma.bPMHistory.findMany();
      res.status(200).json(x)
    } else if (req.method === 'POST') {
      // Process a POST request
      let x = await prisma.bPMHistory.create({
        data: {
          value: parseInt(req.body.heart, 10)
        }
      })
      res.status(201).end();
    } else {
      // Handle any other HTTP method
      res.status(400).json({ message: 'Bad request' })
    }
}