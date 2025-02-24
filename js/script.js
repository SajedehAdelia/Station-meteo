function refreshData() {
    fetch('index.php')
        .then(response => response.text())
        .then(html => {
            document.body.innerHTML = html;
        });
}
setInterval(refreshData, 5000);