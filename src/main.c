// #include "your_Files_here.h"

#include "main.h"

static BrowserState browser;

void InitBrowser(void)
{
    browser.scrollY = 0;
    browser.url[0] = '\0';
    
    ClearScreen();
    RenderBrowserUI("192.168.0.100");
}

void RenderBrowserUI(const char* currentUrl)
{
    DrawRect(0, 0, WSCREEN, BROWSER_NAV_HEIGHT, BROWSER_BAR_COLOR);
    
    DrawRect(10, 8, 50, 24, 0x0045475A);
    SetCursorX(18); SetCursorY(12);
    Print("Go", BROWSER_TEXT_COLOR);

    DrawRect(70, 8, 800, 24, 0x0011111B);
    SetCursorX(80); SetCursorY(12);
    Print(currentUrl, BROWSER_TEXT_COLOR);

    DrawRect(880, 8, WSCREEN, 24, 0x0045475A);
}

void FetchWebPage(DWORD dstIp, const char* path)
{
    char httpRequest[512];
    int len = 0;
    const char* getHeader = "GET ";
    const char* httpVer =
    " HTTP/1.0\r\nHost: server\r\nConnection: close\r\n\r\n";

    for(int i = 0; getHeader[i]; i++) httpRequest[len++] = getHeader[i];
    for(int i = 0; path[i]; i++) httpRequest[len++] = path[i];
    for(int i = 0; httpVer[i]; i++) httpRequest[len++] = httpVer[i];
    httpRequest[len] = '\0';

    SendPacket((LPBYTE)httpRequest, len, dstIp, TCP_PORT);
}

void RenderHTML(const char* htmlData)
{
    DrawRect
    (
        0, BROWSER_NAV_HEIGHT + 1,
        WSCREEN, HSCREEN - BROWSER_NAV_HEIGHT,
        BROWSER_BG_COLOR
    );

    const char* body = htmlData;

    for (int i = 0; htmlData[i] != '\0'; i++)
    {
        if
        (
            htmlData[i] == '\r' && htmlData[i+1] == '\n' && 
            htmlData[i+2] == '\r' && htmlData[i+3] == '\n'
        )
        {
            body = &htmlData[i + 4];
            break;
        }
    }

    int cursorX = 20;
    int cursorY = BROWSER_NAV_HEIGHT + 20;
    int inTag = 0;
    DWORD currentColor = BROWSER_TEXT_COLOR;

    for (int i = 0; body[i] != '\0'; i++)
    {
        if (body[i] == '<') {
            inTag = 1;

            if (body[i+1] == 'h' || body[i+1] == 'H')
            {
                currentColor = 0x00F9E2AF;
            }
            else if (body[i+1] == 'a' || body[i+1] == 'A')
            {
                currentColor = 0x0089B4FA;
            }
            else if (body[i+1] == '/')
            {
                currentColor = BROWSER_TEXT_COLOR;
            }
            continue;
        }

        if (body[i] == '>')
        {
            inTag = 0;
            continue;
        }

        if (!inTag)
        {
            if (body[i] == '\n')
            {
                cursorX = 20;
                cursorY += 16;
            }
            
            else
            {
                SetCursorX(cursorX);
                SetCursorY(cursorY);
                PrintOut(body[i], currentColor);
                cursorX += 8;

                if (cursorX > WSCREEN - 20)
                {
                    cursorX = 20;
                    cursorY += 16;
                }
            }
        }
    }
}
