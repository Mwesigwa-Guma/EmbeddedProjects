# OTA Build and Setup Guide

## Create Certificate

Generate a new certificate using OpenSSL:

```sh
openssl req -x509 -newkey rsa:2048 -keyout ca_key.pem -out ca_cert.pem -days 365 -nodes
```

### Enter Common Name for Certificate

When prompted for the "Common Name" during the certificate generation, enter the IP address or hostname that the ESP32 will connect to:

```sh
Common Name (e.g. server FQDN or YOUR name) []: <your-server-ip-or-hostname>
```

Replace `<your-server-ip-or-hostname>` with the actual IP address or hostname of your server.

## Copy Binary Object to Build Directory

Copy the firmware file to the build directory:

```sh
cp ../../httpserver/build/httpserver.bin .
```

## Start Server

Start the server with the generated certificate:

```sh
openssl s_server -WWW -key ca_key.pem -cert ca_cert.pem -port 8070
```

## Copy Certificate to Server Certificates Directory

Copy the generated certificate to the `../server_certs` directory:

```sh
cp ca_cert.pem ../server_certs/
```

## Add Certificate to Program Programmatically

### Format Certificate Properly

Format the certificate to be included in the program:

```sh
awk 'NF {sub(/\r/, ""); printf "%s\\n", $0;}' ../server_certs/ca_cert.pem
```

### Copy Output into `secrets.h` File

Copy the formatted certificate output into the `secrets.h` file and save it in a constant variable:

```c
const char* ca_cert = \
                    "-----BEGIN CERTIFICATE-----\n" \
                    "MIID.....YourCertContent.....\n" \
                    "-----END CERTIFICATE-----\n";
```

### Configure HTTP Client

Configure the ESP32 HTTP client with the certificate:

```c
esp_http_client_config_t config = {
    .url = ******,
    .cert_pem = ca_cert,
    .event_handler = ********,
    .keep_alive_enable = true,
};
```

## Build and Flash Code to ESP32 Board

Build the project and flash the code to the ESP32 board:

```sh
idf.py -p /dev/tty.usbserial-110 flash monitor
```

## Troubleshooting

### Ping Server for Verification

Verify the server configuration using the `curl` command:

```sh
curl -v https://localhost:8070/<firmware-image-filename>
```

Verify that the server is running and accessible by pinging it:

```sh
ping https://localhost:8070
```

If the server is running on a different machine, replace `localhost` with the server's IP address.
