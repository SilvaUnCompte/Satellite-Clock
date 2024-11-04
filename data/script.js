
var ssid_field = document.getElementById("ssid");
var password_field = document.getElementById("password");
var utc_field = document.getElementById("utc");

var update_config_button = document.getElementById("update-config");
var update_time_button = document.getElementById("update-time");
var test_wifi_button = document.getElementById("test-wifi");

var test_satellite_button = document.getElementById("test-satellite");
var satellite_nb = document.getElementById("satellite-nb");

var confirm_message = document.getElementById("confirm-message");
var connection_status = document.getElementById("connection-status");

function init() {
    get_config();
    update_config_button.addEventListener("click", update_config);
    test_wifi_button.addEventListener("click", update_config);
    update_time_button.addEventListener("click", update_time);
    test_satellite_button.addEventListener("click", get_satellite_count);
}

function get_config() {
    var url = "/get-config";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            ssid_field.value = data.ssid;
            password_field.value = data.password;
            utc_field.value = data.utc;
        });
}

function get_connection_status() {
    connection_status.innerHTML = "Connecting...";
    var connection_status_timeout = setTimeout(() => {
        connection_status.innerHTML = "Timeout";
    }, 6000);

    var url = "/get-connection-status";
    fetch(url)
        .then(response => response.json())
        .then(data => {
            clearInterval(connection_status_timeout);
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
                    connection_status.innerHTML = "Connection Established";
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
}

function update_config() {
    var url = "/update-config?ssid=" + ssid_field.value + "&password=" + password_field.value + "&utc=" + utc_field.value;
    fetch(url)
        .then(data => console.log(data));

    get_connection_status();
}

function update_time() {
    confirm_message.innerHTML = "Updating...";
    fetch("/update-time")
        .then(response => response.json())
        .then(data => confirm_message.innerHTML = data.confirm_message);
}

function get_satellite_count() {
    satellite_nb.innerHTML = "Loading...";
    fetch("/get-satellite-count")
        .then(response => response.json())
        .then(data => satellite_nb.innerHTML = data);
}