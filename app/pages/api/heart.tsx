export default function handler(req, res) {
    if (req.method === 'GET') {
      // Process a GET request
      res.status(200).json({
        timestamp: '09/01/2022 - 15:00:00',
        bpm: '70'
      })
    } else if (req.method === 'POST') {
      // Process a POST request
      res.status(201)
    } else {
      // Handle any other HTTP method
      res.status(400).json({ message: 'Bad request' })
    }
}