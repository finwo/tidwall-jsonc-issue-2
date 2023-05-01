#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "tidwall/json.h"
#include "webview/webview.h"

#ifdef _WIN32
#include <Windows.h>
#endif

static const char html[] = {
#include "./index.h"
};

struct ex_context {
  webview_t w;
};

void fn_set_title(const char *seq, const char *req, void *udata) {
  struct ex_context *ctx = udata;

  printf("\n---[ New set title request ]---\n\n");
  printf("Req: %s\nSeq: %s\n\n", req, seq);

  struct json json = json_parse(req);
  json = json_first(json);

  printf("%.*s\n", (int)json_raw_length(json), json_raw(json));
  char *newTitle = calloc(512, 1);
  json_string_copy(json, newTitle, sizeof(newTitle));

  printf("%s\n", newTitle);
  webview_set_title(ctx->w, newTitle);

  webview_return(ctx->w, seq, 0, "{}");
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInt, HINSTANCE hPrevInst, LPSTR lpCmdLine,
                   int nCmdShow) {
#else
int main() {
#endif

  struct ex_context *ctx = malloc(sizeof(struct ex_context));
  ctx->w = webview_create(0, NULL);

  // Initialize the window
  webview_set_title(ctx->w, "Example");
  webview_set_size(ctx->w, 800, 600, WEBVIEW_HINT_NONE);
  webview_set_html(ctx->w, html);

  // Initialize binding
  webview_bind(ctx->w, "set_title", fn_set_title, ctx);

  // Start the window
  webview_run(ctx->w);
  webview_destroy(ctx->w);

  return 0;
}

