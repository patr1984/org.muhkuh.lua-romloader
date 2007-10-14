// ---------------------------------------------------------------------------
// This file was generated by genwxbind.lua 
//
// Any changes made to this file may be lost when file is regenerated.
// ---------------------------------------------------------------------------

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/wxprec.h"


#ifndef WX_PRECOMP
     #include "wx/wx.h"
#endif

#include "wxlua/include/wxlstate.h"
#include "romloader_usb_wxlua_bindings.h"


// ---------------------------------------------------------------------------
// Bind class romloader
// ---------------------------------------------------------------------------

// Lua MetaTable Tag for Class 'romloader'
int s_wxluatag_romloader = -1;

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_call[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_call(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_call[1] = {{ wxLua_romloader_call, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_call }};
//  void call(unsigned long ulNetxAddress, unsigned long ulParameterR0)
static int LUACALL wxLua_romloader_call(lua_State *L)
{
    wxLuaState wxlState(L);
    // unsigned long ulParameterR0
    unsigned long ulParameterR0 = (long)wxlua_getnumbertype(L, 3);
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call call
    self->call(ulNetxAddress, ulParameterR0);

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_connect[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_connect(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_connect[1] = {{ wxLua_romloader_connect, WXLUAMETHOD_METHOD, 1, 1, s_wxluatagArray_wxLua_romloader_connect }};
//  void connect()
static int LUACALL wxLua_romloader_connect(lua_State *L)
{
    wxLuaState wxlState(L);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call connect
    self->connect();

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_delete[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_delete(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_delete[1] = {{ wxLua_romloader_delete, WXLUAMETHOD_METHOD|WXLUAMETHOD_DELETE, 1, 1, s_wxluatagArray_wxLua_romloader_delete }};
static int LUACALL wxLua_romloader_delete(lua_State *L)
{
    wxLuaState wxlState(L);
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // if removed from tracked mem list, reset the tag so that gc() is not called on this object.
    if ((self != NULL) && wxlState.RemoveTrackedObject(self, wxLuaState::DELETE_CLEAR_OBJECT))
    {
        lua_pushnil(L);
        lua_setmetatable(L, -2);
    }
    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_disconnect[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_disconnect(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_disconnect[1] = {{ wxLua_romloader_disconnect, WXLUAMETHOD_METHOD, 1, 1, s_wxluatagArray_wxLua_romloader_disconnect }};
//  void disconnect()
static int LUACALL wxLua_romloader_disconnect(lua_State *L)
{
    wxLuaState wxlState(L);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call disconnect
    self->disconnect();

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_get_name[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_get_name(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_get_name[1] = {{ wxLua_romloader_get_name, WXLUAMETHOD_METHOD, 1, 1, s_wxluatagArray_wxLua_romloader_get_name }};
//  wxString get_name()
static int LUACALL wxLua_romloader_get_name(lua_State *L)
{
    wxLuaState wxlState(L);
    wxString returns;
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call get_name
    returns = (self->get_name());
    // push the result string
    wxlState.lua_PushLString(returns,returns.Len());

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_get_typ[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_get_typ(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_get_typ[1] = {{ wxLua_romloader_get_typ, WXLUAMETHOD_METHOD, 1, 1, s_wxluatagArray_wxLua_romloader_get_typ }};
//  wxString get_typ()
static int LUACALL wxLua_romloader_get_typ(lua_State *L)
{
    wxLuaState wxlState(L);
    wxString returns;
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call get_typ
    returns = (self->get_typ());
    // push the result string
    wxlState.lua_PushLString(returns,returns.Len());

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_is_connected[] = { &s_wxluatag_romloader, NULL };
static int LUACALL wxLua_romloader_is_connected(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_is_connected[1] = {{ wxLua_romloader_is_connected, WXLUAMETHOD_METHOD, 1, 1, s_wxluatagArray_wxLua_romloader_is_connected }};
//  bool is_connected()
static int LUACALL wxLua_romloader_is_connected(lua_State *L)
{
    wxLuaState wxlState(L);
    bool returns;
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call is_connected
    returns = (self->is_connected());
    // push the result flag
    lua_pushboolean(L, returns);

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_read_data08[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_read_data08(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_read_data08[1] = {{ wxLua_romloader_read_data08, WXLUAMETHOD_METHOD, 2, 2, s_wxluatagArray_wxLua_romloader_read_data08 }};
//  unsigned char read_data08(unsigned long ulNetxAddress)
static int LUACALL wxLua_romloader_read_data08(lua_State *L)
{
    wxLuaState wxlState(L);
    unsigned char returns;
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call read_data08
    returns = (self->read_data08(ulNetxAddress));
    // push the result number
    lua_pushnumber(L, returns);

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_read_data16[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_read_data16(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_read_data16[1] = {{ wxLua_romloader_read_data16, WXLUAMETHOD_METHOD, 2, 2, s_wxluatagArray_wxLua_romloader_read_data16 }};
//  unsigned short read_data16(unsigned long ulNetxAddress)
static int LUACALL wxLua_romloader_read_data16(lua_State *L)
{
    wxLuaState wxlState(L);
    unsigned short returns;
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call read_data16
    returns = (self->read_data16(ulNetxAddress));
    // push the result number
    lua_pushnumber(L, returns);

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_read_data32[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_read_data32(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_read_data32[1] = {{ wxLua_romloader_read_data32, WXLUAMETHOD_METHOD, 2, 2, s_wxluatagArray_wxLua_romloader_read_data32 }};
//  unsigned long read_data32(unsigned long ulNetxAddress)
static int LUACALL wxLua_romloader_read_data32(lua_State *L)
{
    wxLuaState wxlState(L);
    unsigned long returns;
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call read_data32
    returns = (self->read_data32(ulNetxAddress));
    // push the result number
    lua_pushnumber(L, returns);

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_read_image[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_read_image(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_read_image[1] = {{ wxLua_romloader_read_image, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_read_image }};
//  wxString read_image(unsigned long ulNetxAddress, unsigned long ulSize)
static int LUACALL wxLua_romloader_read_image(lua_State *L)
{
    wxLuaState wxlState(L);
    wxString returns;
    // unsigned long ulSize
    unsigned long ulSize = (long)wxlua_getnumbertype(L, 3);
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call read_image
    returns = (self->read_image(ulNetxAddress, ulSize));
    // push the result string
    wxlState.lua_PushLString(returns,returns.Len());

    return 1;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_write_data08[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_write_data08(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_write_data08[1] = {{ wxLua_romloader_write_data08, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_write_data08 }};
//  void write_data08(unsigned long ulNetxAddress, unsigned char bData)
static int LUACALL wxLua_romloader_write_data08(lua_State *L)
{
    wxLuaState wxlState(L);
    // unsigned char bData
    unsigned char bData = (char)wxlua_getnumbertype(L, 3);
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call write_data08
    self->write_data08(ulNetxAddress, bData);

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_write_data16[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_write_data16(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_write_data16[1] = {{ wxLua_romloader_write_data16, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_write_data16 }};
//  void write_data16(unsigned long ulNetxAddress, unsigned short usData)
static int LUACALL wxLua_romloader_write_data16(lua_State *L)
{
    wxLuaState wxlState(L);
    // unsigned short usData
    unsigned short usData = (short)wxlua_getnumbertype(L, 3);
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call write_data16
    self->write_data16(ulNetxAddress, usData);

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_write_data32[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_Number, NULL };
static int LUACALL wxLua_romloader_write_data32(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_write_data32[1] = {{ wxLua_romloader_write_data32, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_write_data32 }};
//  void write_data32(unsigned long ulNetxAddress, unsigned long ulData)
static int LUACALL wxLua_romloader_write_data32(lua_State *L)
{
    wxLuaState wxlState(L);
    // unsigned long ulData
    unsigned long ulData = (long)wxlua_getnumbertype(L, 3);
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call write_data32
    self->write_data32(ulNetxAddress, ulData);

    return 0;
}

static wxLuaArgTag s_wxluatagArray_wxLua_romloader_write_image[] = { &s_wxluatag_romloader, &s_wxluaarg_Number, &s_wxluaarg_String, NULL };
static int LUACALL wxLua_romloader_write_image(lua_State *L);
static wxLuaBindCFunc s_wxluafunc_wxLua_romloader_write_image[1] = {{ wxLua_romloader_write_image, WXLUAMETHOD_METHOD, 3, 3, s_wxluatagArray_wxLua_romloader_write_image }};
// %override wxLua_romloader_write_image
static int LUACALL wxLua_romloader_write_image(lua_State *L)
{
    wxLuaState wxlState(L);
    // wxString strData
    wxString strData;
    size_t sizLen;
    const char *pcBuf;
    pcBuf = lua_tolstring(L, 3, &sizLen);
    if( sizLen==0 )
    {
        strData = wxEmptyString;
    }
    else
    {
        strData = wxString::From8BitData(pcBuf, sizLen);
    }
    // unsigned long ulNetxAddress
    unsigned long ulNetxAddress = (long)wxlua_getnumbertype(L, 2);
    // get this
    romloader * self = (romloader *)wxlState.GetUserDataType(1, s_wxluatag_romloader);
    // call write_image
    self->write_image(ulNetxAddress, strData);

    return 0;
}




// Map Lua Class Methods to C Binding Functions
wxLuaBindMethod romloader_methods[] = {
    { "call", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_call, 1, NULL },
    { "connect", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_connect, 1, NULL },
    { "delete", WXLUAMETHOD_METHOD|WXLUAMETHOD_DELETE, s_wxluafunc_wxLua_romloader_delete, 1, NULL },
    { "disconnect", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_disconnect, 1, NULL },
    { "get_name", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_get_name, 1, NULL },
    { "get_typ", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_get_typ, 1, NULL },
    { "is_connected", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_is_connected, 1, NULL },
    { "read_data08", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_read_data08, 1, NULL },
    { "read_data16", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_read_data16, 1, NULL },
    { "read_data32", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_read_data32, 1, NULL },
    { "read_image", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_read_image, 1, NULL },
    { "write_data08", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_write_data08, 1, NULL },
    { "write_data16", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_write_data16, 1, NULL },
    { "write_data32", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_write_data32, 1, NULL },
    { "write_image", WXLUAMETHOD_METHOD, s_wxluafunc_wxLua_romloader_write_image, 1, NULL },
    { 0, 0, 0, 0 },
};

int romloader_methodCount = sizeof(romloader_methods)/sizeof(wxLuaBindMethod) - 1;


