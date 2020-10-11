require('dotenv').config();

// Express App Setup
const express = require('express');
const http = require('http');
const bodyParser = require('body-parser');
const cors = require('cors');
const execSync = require('child_process').execSync;

// Initialization
const app = express();
app.use(cors());
app.use(bodyParser.json());


app.post('/stream', async (req, res) => {
    try {
        console.log(req.body);
        const name = req.body.streamName;
        const url = req.body.url;
        const response = await execSync(`wget ${req.body.url} -P /opt/${req.body.streamName} `);
        console.log('response ', response);

        res.status(201).send(`Item created: `);
    }
    catch (ex) {
        res.status(400).send(ex.message);
    }
});


// Server
const port = process.env.PORT || 3001;
const server = http.createServer(app);
server.listen(port, () => console.log(`Server running on port ${port}`));