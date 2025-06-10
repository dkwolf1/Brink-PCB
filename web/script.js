function sendCommand(id, state) {
  fetch('/switch/' + id + '?turn=' + state)
    .then(res => console.log(id + ' ' + state + ' -> ' + res.status));
}

function loadSensors() {
  fetch('/sensors')
    .then(res => res.json())
    .then(data => {
      const tbody = document.getElementById('sensorBody');
      tbody.innerHTML = '';
      data.sensors.forEach(s => {
        const row = document.createElement('tr');
        row.innerHTML = `<td>${s.name}</td><td>${s.value}</td>`;
        tbody.appendChild(row);
      });
    });
}

function saveNetwork() {
  const ip = document.getElementById('ip').value;
  const subnet = document.getElementById('subnet').value;
  const gateway = document.getElementById('gateway').value;
  fetch('/network', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ ip, subnet, gateway })
  }).then(res => alert('Network update ' + res.status));
}

window.onload = loadSensors;
