const express = require("express");

const PORT = 3000;

const app = express();

app.use(express.json());
// app.use(function(req, res, next) {
//     req.rawBody = '';
//     req.setEncoding('utf8');
//
//     req.on('data', function(chunk) {
//         req.rawBody += chunk;
//     });
//
//     req.on('end', function() {
//         next();
//     });
// });

app.get("/status", (req, res) => res.json({ status: "OK", version: "0.1" }))
app.post("/test", (req, res) => {
    console.log(req.body);
    res.json({status: "OK"})
})

app.listen(PORT, () => console.log(`Launched at :${PORT}`))