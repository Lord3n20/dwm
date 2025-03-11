/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Monaco Nerd Font:size=10" };
static const char dmenufont[]       = "Monaco Nerd Font Mono:size=10";

static char normbgcolor[]           = "#000000";
static char normbordercolor[]       = "#000000";
static char normfgcolor[]           = "#ffffff";
static char selfgcolor[]            = "#ffffff";
static char selbordercolor[]        = "#000000";
static char selbgcolor[]            = "#000000";
static const unsigned int baralpha = 140;
static const unsigned int borderalpha = OPAQUE;
static char *colors[][3] = {
       /*               fg           bg           border   */
       [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
       [SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

static const unsigned int alphas[][3]      = {
    /*               fg      bg        border*/
    [SchemeNorm] = { OPAQUE, baralpha, borderalpha },
    [SchemeSel]  = { OPAQUE, baralpha-50, borderalpha },
};


/* tagging */
static const char *tags[] = { "", "", "", "", "", "6", "7", "8" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                        instance    title       tags mask     isfloating   monitor */
	{ "Min",  NULL,       NULL,       1 << 1,       0,           -1 },
	{ "discord",                    NULL,       NULL,       1 << 2,       0,           -1 },
	{ "betterbird",                 NULL,       NULL,       1 << 3,       0,           -1 },
	{ "steam",                      NULL,       NULL,       1 << 4,       0,           -1 },
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
static const char *dmenucmd[]= { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbordercolor, "-sf", selfgcolor, NULL };
static const char *termcmd[] = { "/usr/local/bin/st", NULL };

static const char *upvol[]   = { "sh", "/home/enzo/.btndo.sh", "vol", "up", NULL };
static const char *downvol[] = { "sh", "/home/enzo/.btndo.sh", "vol", "down", NULL };
static const char *mutevol[] = { "sh", "/home/enzo/.btndo.sh", "vol", "mute", NULL };
static const char *mutemic[] = { "sh", "/home/enzo/.btndo.sh", "mic", "mute", NULL };
static const char *uplight[] = { "sh", "/home/enzo/.btndo.sh", "light", "up", NULL };
static const char *downlig[] = { "sh", "/home/enzo/.btndo.sh", "light", "down", NULL };
static const char *flame[] = { "sh", "/home/enzo/.btndo.sh", "screen", NULL };
static const char *bgrel[] = { "sh", "/home/enzo/.btndo.sh", "reloadbg", NULL };
static const char *playback[] = { "sh", "/home/enzo/.btndo.sh", "playback", "toggle", NULL };
static const char *playbackP[] = { "sh", "/home/enzo/.btndo.sh", "playback", "again", NULL };
static const char *playbackS[] = { "sh", "/home/enzo/.btndo.sh", "playback", "skip", NULL };
static const char *shutcmd[] = {"sudo","poweroff",NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ 0,                       XF86XK_Favorites, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_Tab,    zoom,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,			                  XK_Right,  focusstack,     {.i = +1} },
	{ MODKEY,                       XK_Left,   focusstack,     {.i = -1} },
	{ MODKEY,			                  XK_e,      setmfact,       {.f = +0.01} },
	{ MODKEY,		                  	XK_w,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ 0,                            XF86XK_MonBrightnessUp,    spawn, {.v = uplight } },
	{ 0,                            XF86XK_MonBrightnessDown,  spawn, {.v = downlig } },
	{ 0,                            XF86XK_AudioLowerVolume,   spawn, {.v = downvol } },
	{ 0,                            XF86XK_AudioMute,          spawn, {.v = mutevol } },
	{ 0,                            XF86XK_AudioMicMute,       spawn, {.v = mutemic } },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn, {.v = upvol   } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,                       XK_x,      quit,           {0} },
	{ MODKEY,                       XK_y,      spawn,          {.v = shutcmd } },
	{ MODKEY,                       XK_f,      spawn,          {.v = flame } },
	{ MODKEY,                       XK_r,      spawn,          {.v = bgrel } },
	{ MODKEY,                       XF86XK_AudioLowerVolume,   spawn, {.v = playbackP } },
	{ MODKEY,                       XF86XK_AudioMute,          spawn, {.v = playback } },
  { MODKEY,                       XF86XK_AudioRaiseVolume,   spawn, {.v = playbackS   } },
	{ 0,                            XF86XK_AudioPrev,          spawn, {.v = playbackP } },
	{ 0,                            XF86XK_AudioPlay,          spawn, {.v = playback } },
  { 0,                            XF86XK_AudioNext,          spawn, {.v = playbackS   } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
};

