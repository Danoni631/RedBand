#ifndef BROWSER_H
#define BROWSER_H

#define BROWSER_NAV_HEIGHT 40
#define BROWSER_BG_COLOR   0x001E1E2E // Dark theme
#define BROWSER_BAR_COLOR  0x00313244
#define BROWSER_TEXT_COLOR 0x00CDD6F4

typedef struct
{
    char url[256];
    char pageBuffer[8192];
    int scrollY;
} BrowserState;

void InitBrowser(void);
void RenderBrowserUI(const char* currentUrl);
void FetchWebPage(DWORD dstIp, const char* path);
void RenderHTML(const char* htmlContent);

#endif