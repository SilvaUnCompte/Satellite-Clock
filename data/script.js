
var ssid_field = document.getElementById("ssid");
var password_field = document.getElementById("password");
var update_credentials_button = document.getElementById("update");
var connection_status = document.getElementById("connection-status");

function init() {
    get_credentials();
    update_credentials_button.addEventListener("click", update_credentials);
    get_connection_status();
}

function get_credentials() {
    var url = "/get-credentials";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            ssid_field.value = data.ssid;
            password_field.value = data.password;
        });
}

function get_connection_status() {  // TODO: Stoper la boucle si connecté. Effacer le champ après 5 secondes.
    var url = "/get-connection-status";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            switch (data) {
                case 0:
                    connection_status.innerHTML = "Idle";
                    break;
                case 1:
                    connection_status.innerHTML = "No SSID Available";
                    break;
                case 2:
                    connection_status.innerHTML = "Scan Completed";
                    break;
                case 3:
                    connection_status.innerHTML = "Connected";
                    break;
                case 4:
                    connection_status.innerHTML = "Connection Failed";
                    break;
                case 5:
                    connection_status.innerHTML = "Connection Lost";
                    break;
                case 6:
                    connection_status.innerHTML = "Disconnected";
                    break;
                default:
                    connection_status.innerHTML = "Unknown";
                    break;
            }
        });

    setTimeout(get_connection_status, 1000);
}

function update_credentials() {
    var url = "/update-credentials?ssid=" + ssid_field.value + "&password=" + password_field.value;
    fetch(url)
        .then(response => response.json())
        .then(data => console.log(data));
}