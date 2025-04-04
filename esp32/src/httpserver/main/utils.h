#include <esp_log.h>
#include <stdlib.h>
#include <esp_http_server.h>
#include "esp_tls_crypto.h"
#include "/Users/mwesigwaguma/Desktop/repos/Projects/EmbeddedProjects/esp32/src/common/secrets.h"

typedef struct {
    char    *username;
    char    *password;
} basic_auth_info_t;

static void httpd_register_basic_auth(httpd_handle_t server);
static char *http_auth_basic(const char *username, const char *password);
static esp_err_t basic_auth_get_handler(httpd_req_t *req);
void ngx_unescape_uri(u_char **dst, u_char **src, size_t size, unsigned int type);
void uri_decode(char *dest, const char *src, size_t len);

