// Connexion à la base MySQL en direct
const dbConfig = {
  host: "localhost",
  user: "root",
  password: "",
  database: "mqtt_db"
};

async function fetchData() {
  const connection = await window.mysql.createConnection(dbConfig);
  const [rows] = await connection.execute("SELECT id, value, timestamp FROM data ORDER BY timestamp DESC");
  connection.end();
  return rows;
}

// Charger les données historiques depuis MySQL
fetchData().then(data => {
  const table = document.getElementById('data-table');
  data.forEach(row => {
      const tr = document.createElement('tr');
      tr.innerHTML = `<td>${row.id}</td><td>${row.value}</td><td>${row.timestamp}</td>`;
      table.appendChild(tr);
  });
});

// Connexion au broker MQTT
const client = mqtt.connect('ws://localhost:1884');

client.on('connect', () => {
  console.log('Connecté à MQTT');
  client.subscribe('mon/topic');
});

client.on('message', (topic, message) => {
  const table = document.getElementById('data-table');
  const data = JSON.parse(message.toString());
  const tr = document.createElement('tr');
  tr.innerHTML = `<td>${data.id}</td><td>${data.value}</td><td>${data.timestamp}</td>`;
  table.prepend(tr);
});