#include "device\alpacaHandler.h"
#include "device\struct.h"

AlpacaHandler::AlpacaHandler(ESP8266WebServer *server)
{
    _server = server;
    switchDevice = new SwitchDevice();
    // switchDevice->writeEEPROM();
    switchDevice->readEEPROM();

    serverTransactionID = 0;
}

void AlpacaHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.traceln("%d" CR, i);
        Log.traceln("%s" CR, _server->argName(i));
        Log.traceln("%s" CR, _server->arg(i));
        Log.traceln("--------------------------");
    }
}

void AlpacaHandler::incrementServerTransID()
{
    serverTransactionID++;
}

/**************************************************************
 * ASCOM Alpaca Management API - Management Interface Methods *
 **************************************************************/
void AlpacaHandler::handlerMgmtVersions()
{
    Log.traceln("handlerMgmtVersions called...");
    if (conformanceCheck() == false){
        return;
    }
    incrementServerTransID();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void AlpacaHandler::handlerMgmtDescription()
{
    Log.traceln("handlerMgmtDescription called");
    if (conformanceCheck() == false){
        return;
    }

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "text/json", output);
        
    }
}

void AlpacaHandler::handlerMgmtConfiguredDevices()
{
    Log.traceln("handlerMgmtConfiguredDevices called");
    if (conformanceCheck() == false){
        return;
    }
    
    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "text/json", output);
        
    }
}

/*****************************************************************
 * ASCOM Alpaca Device API - ASCOM Methods Common To All Devices *
 *****************************************************************/
void AlpacaHandler::handleAction()
{
    Log.traceln("handleAction called");
    if (conformanceCheck() == false){
        return;
    }
    
    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void AlpacaHandler::handleCommandBlind()
{
    Log.traceln("handleCommandBlind called");
    if (conformanceCheck() == false){
        return;
    }
    
    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnEmpty("", 0);
}

void AlpacaHandler::handleCommandBool()
{
    Log.traceln("handleCommandBool called");
    if (conformanceCheck() == false){
        return;
    }
    
    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void AlpacaHandler::handleCommandString()
{
    Log.traceln("handleCommandBool called");
    if (conformanceCheck() == false){
        return;
    }

    String deviceType = _server->arg("device_type");
    u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command.c_str());
    Log.traceln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

void AlpacaHandler::handlerConnected()
{
    Log.traceln("handlerConnected called");
    if (conformanceCheck() == false){
        return;
    }

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");

        String deviceType = _server->arg("device_type");
        //uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(switchDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        Log.traceln("handlerConnected POST called");

        // String _connected = _server->arg("Connected");
        switchDevice->connected = (bool)_server->arg("Connected");
        // Log.traceln("%t", CR, switchDevice->connected);

        returnEmpty("", 0);
    }
}

void AlpacaHandler::handlerDescriptionGet()
{
    Log.traceln("handlerDescriptionGet called");
    if (conformanceCheck() == false){
        return;
    }
    returnStringValue(DESCRIPTION, "", 0);
}

void AlpacaHandler::handlerDriverInfoGet()
{
    Log.traceln("handlerDriverInfoGet called");
    if (conformanceCheck() == false){
        return;
    }
    returnStringValue(DRIVER_INFO, "", 0);
}

void AlpacaHandler::handlerDriverVersionGet()
{
    Log.traceln("handlerDriverVersionGet called");
    if (conformanceCheck() == false){
        return;
    }
    returnStringValue(DRIVER_VERSION, "", 0);
}

void AlpacaHandler::handlerInterfaceVersionGet()
{
    Log.traceln("handlerInterfaceVersionGet called");
    if (conformanceCheck() == false){
        return;
    }
    returnIntValue(1, "", 0);
}

void AlpacaHandler::handlerNameGet()
{
    Log.traceln("handlerNameGet called");
    if (conformanceCheck() == false){
        return;
    }
    returnStringValue(DEVICE_NAME, "", 0);
}

void AlpacaHandler::handlerSupportedActionsGet()
{
    Log.traceln("handlerSupportedActionsGet called");
    if (conformanceCheck() == false){
        return;
    }

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");
    array.add("maxswitch");
    array.add("canwrite");
    array.add("getswitchdescription");
    array.add("getswitch");
    array.add("getswitchname");
    array.add("getswitchvalue");
    array.add("minswitchvalue");
    array.add("maxswitchvalue");
    array.add("switchstep");

    returnJsonArrayValue(array, "", 0);
    
}

/*****************************************************
 * ASCOM Alpaca Device API - Switch Specific Methods *
 *****************************************************/
void AlpacaHandler::handlerDriver0Maxswitch()
{
    Log.traceln("handlerDriver0Maxswitch called");
    if (conformanceCheck() == false){
        return;
    }
    
    returnIntValue(NR_OF_CHANNELS, "", 0);
}

void AlpacaHandler::handlerDriver0CanWrite()
{
    Log.traceln("handlerDriver0CanWrite called");
    if (conformanceCheck() == false){
        return;
    }
    
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnBoolValue(true, "", 0);
}

void AlpacaHandler::handlerDriver0SwitchState()
{
    Log.traceln("handlerDriver0SwitchState called");
    if (conformanceCheck() == false){
        return;
    }
    
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchState called");

        returnBoolValue(switchDevice->getSwitchState(id), "", 0);
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchState called");
        bool val = (bool)_server->arg("State");

        switchDevice->setSwitchState(id, val);
        returnEmpty("", 0);
    }
}

void AlpacaHandler::handlerDriver0SwitchDescription()
{
    Log.traceln("handlerDriver0SwitchDescription called");
    if (conformanceCheck() == false){
        return;
    }
    
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnStringValue(switchDevice->getSwitchDesc(id), "", 0);
}

void AlpacaHandler::handlerDriver0SwitchName()
{
    Log.traceln("handlerDriver0SwitchName called");
    if (conformanceCheck() == false){
        return;
    }

    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    returnStringValue(switchDevice->getSwitchName(id), "", 0);
}

void AlpacaHandler::handlerDriver0SwitchValue()
{
    Log.traceln("handlerDriver0SwitchValue called");
    if (conformanceCheck() == false){
        return;
    }

    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("GET SwitchValue called");
        returnDoubleValue(switchDevice->getSwitchValue(id), "", 0);
        
    }
    else if (_server->method() == HTTP_PUT)
    {
        Log.traceln("PUT SwitchValue called");
        double val = (double)_server->arg("Value").toDouble();
        
        switchDevice->setSwitchValue(id, val);
        returnEmpty("", 0);
    }


}

void AlpacaHandler::handlerDriver0MinSwitchValue()
{
    Log.traceln("handlerDriver0MinSwitchValue called");
    if (conformanceCheck() == false){
        return;
    }

    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(switchDevice->getSwitchMin(id), "", 0);
}

void AlpacaHandler::handlerDriver0MaxSwitchValue()
{
    Log.traceln("handlerDriver0MaxSwitchValue called");
    if (conformanceCheck() == false){
        return;
    }

    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(switchDevice->getSwitchMax(id), "", 0);
}

void AlpacaHandler::handlerDriver0SwitchStep()
{
    Log.traceln("handlerDriver0SwitchStep called");
    if (conformanceCheck() == false){
        return;
    }

    u_int32_t id = (uint32_t)_server->arg("ID").toInt();
    
    returnDoubleValue(switchDevice->getSwitchStep(id), "", 0);
}

/***********************************************
          Custom handlers for webpage
***********************************************/
bool AlpacaHandler::getSwitchState(uint32_t id)
{
    return switchDevice->getSwitchState(id);
}

void AlpacaHandler::setSwitchState(uint32_t id, bool state)
{
    switchDevice->setSwitchState(id, state);
}

String AlpacaHandler::getSwitchName(uint32_t id)
{
    return switchDevice->getSwitchName(id);
}

void AlpacaHandler::setSwitchName(uint32_t id, String name)
{
    switchDevice->setSwitchName(id, name);
}

void AlpacaHandler::storeEEPROM()
{
    switchDevice->writeEEPROM();
}

String AlpacaHandler::getSwitchState()
{
    return switchDevice->getSwitchState();
}

/*********************************************
          Alpaca Conformance Methods
*********************************************/
bool AlpacaHandler::conformanceCheck(){
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    if (_server->arg("ClientID").indexOf("-") >= 0 || clientID == 0){
        returnError400("ClientID invalid");
        return false;
    }
    if (_server->arg("ClientTransactionID").indexOf("-") >= 0 || transID == 0){
        returnError400("ClientTransactionID invalid");
        return false;
    }
    return true;
}

/*********************************************
          Handler Return Methods
*********************************************/
void AlpacaHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnError400(String errMsg)
{
    incrementServerTransID();
    Log.traceln(F("Returning: Error 400 = %s" CR), errMsg.c_str());

    _server->send(400, "text/plain", errMsg);
}

void AlpacaHandler::returnError500(String errMsg)
{
    incrementServerTransID();
    Log.traceln(F("Returning: Error 500 = %s" CR), errMsg.c_str());

    _server->send(500, "text/plain", errMsg);
}

void AlpacaHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnIntValue(uint32_t val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}

void AlpacaHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "application/json", output);
}
