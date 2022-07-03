/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono NF:size=12", "Noto Color Emoji:pixelsize=18:antialias=true:autohint=true"  };
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class      instance    title       tags mask     isfloating   monitor */
  { "Gimp",     NULL,       NULL,       0,            1,           -1 },
  { "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, "-c", "-l", "20", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *backlight[2][4] = {
    {"backlight", "-inc", NULL},
    {"backlight", "-dec", NULL}
};
static const char *volume[3][4] = {
    {"pulsemixer-wrapper", "--change-volume", "+5", NULL},
    {"pulsemixer-wrapper", "--change-volume", "-5", NULL},
    {"pulsemixer-wrapper", "--toggle-mute",   "",   NULL}
};

#include <X11/XF86keysym.h>
static Key keys[] = {
  /* modifier        key                       function        argument */
  { 0,                XF86XK_AudioLowerVolume,  spawn,          {.v = volume[1]} },         // Lower volume
  { 0,                XF86XK_AudioRaiseVolume,  spawn,          {.v = volume[0]} },         // Raise volume
  { 0,                XF86XK_AudioMute,         spawn,          {.v = volume[2]} },         // Mute volume
  { 0,                XF86XK_MonBrightnessDown, spawn,          {.v = backlight[1]} },      // Decrease backlight of the display
  { 0,                XF86XK_MonBrightnessUp,   spawn,          {.v = backlight[0]} },      // Increase backlight of the display
  { 0,                XK_Print,                 spawn,          SHCMD("flameshot gui") },   // Screenshot utility
  { MODKEY,           XK_Tab,                   view,           {0} },                      // Cycle between most recent tags
  { MODKEY,           XK_b,                     togglebar,      {0} },                      // Toggle dwm toolbar
  { MODKEY,           XK_q,                     killclient,     {0} },                      // Close application
  { MODKEY|ShiftMask, XK_q,                     quit,           {0} },                      // Hard quit dwm
  { MODKEY,           XK_d,                     spawn,          {.v = dmenucmd} },          // Application menu
  { MODKEY,           XK_j,                     focusstack,     {.i = +1} },                // Switch window focus within tag
  { MODKEY,           XK_k,                     focusstack,     {.i = -1} },                // Switch window focus within tag
  { MODKEY,           XK_h,                     setmfact,       {.f = -0.05} },             // Grow / Shrink windwos in tag
  { MODKEY,           XK_l,                     setmfact,       {.f = +0.05} },             // Grow / Shrink windwos in tag
  { MODKEY,           XK_f,                     setlayout,      {.v = &layouts[1]} },       // Set layout to floating
  { MODKEY,           XK_m,                     setlayout,      {.v = &layouts[2]} },       // Set layout to monocle
  { MODKEY,           XK_space,                 setlayout,      {0} },                      // Reset layout
  { MODKEY,           XK_p,                     spawn,          SHCMD("passmenu") },        // Open pass in dmenu
  { MODKEY,           XK_t,                     spawn,          {.v = termcmd} },           // Open terminal
  { MODKEY,           XK_w,                     spawn,          SHCMD("$BROWSER") },        // Open browser
  { MODKEY|ShiftMask, XK_l,                     spawn,          SHCMD("slock") },           // Lock the display
  { MODKEY|ShiftMask, XK_space,                 togglefloating, {0} },                      // Set floating window for application
  { MODKEY,           XK_Return,                zoom,           {0} },                      // Focused window becomes the main application in tag
  { MODKEY,           XK_0,                     view,           {.ui = ~0} },               // Focused window available in all tags
  { MODKEY,           XK_comma,                 focusmon,       {.i = -1} },                // Move application within tag
  { MODKEY,           XK_period,                focusmon,       {.i = +1} },                // Move application within tag
  { MODKEY|ShiftMask, XK_0,                     tag,            {.ui = ~0} },               // Move application between tags
  { MODKEY|ShiftMask, XK_Left,                  tagmon,         {.i = -1} },                // Move application to different display
  { MODKEY|ShiftMask, XK_Right,                 tagmon,         {.i = +1} },                // Move application to different display
  { MODKEY,           XK_minus,                 setgaps,        {.i = -1 } },               // Decreases window gaps
  { MODKEY,           XK_equal,                 setgaps,        {.i = +1 } },               // Increases window gaps
  { MODKEY|ShiftMask, XK_equal,                 setgaps,        {.i = 0  } },               // Resets window gaps

  TAGKEYS(            XK_1,                     0)
  TAGKEYS(            XK_2,                     1)
  TAGKEYS(            XK_3,                     2)
  TAGKEYS(            XK_4,                     3)
  TAGKEYS(            XK_5,                     4)
  TAGKEYS(            XK_6,                     5)
  TAGKEYS(            XK_7,                     6)
  TAGKEYS(            XK_8,                     7)
  TAGKEYS(            XK_9,                     8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkWinTitle,          0,              Button2,        zoom,           {0} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

