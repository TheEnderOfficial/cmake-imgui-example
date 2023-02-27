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
//
let results = [
    {id: 1, name: "admin", length: 200}
];

app.get("/status", (req, res) => res.json({ status: "OK", version: "dev" }))
app.post("/result", (req, res) => {
    const {name, length} = req.body;
    let lastId = results[results.length - 1].id
    results.push({name, length, id: lastId + 1})
    res.json({status: "OK", id: lastId + 1})
})
app.get("/top", (req, res) => res.json({top: results.sort(i => i.length).slice(0, 99)}))
app.listen(PORT, () => console.log(`Launched at :${PORT}`))