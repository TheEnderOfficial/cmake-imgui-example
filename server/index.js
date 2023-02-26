const express = require("express");

const PORT = 3000;

const app = express();

app.use(express.json());

app.get("/status", (req, res) => res.json({ status: "OK", version: "0.1" }))

app.listen(PORT, () => console.log(`Launched at :${PORT}`))