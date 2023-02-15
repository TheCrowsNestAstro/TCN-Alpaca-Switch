#include <Arduino.h>

const char index_html_header[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>


body { 
  margin: 0;
  font-family: Arial, Helvetica, sans-serif;
  background-color: #1a1a1a;
  color: #d8dbe0;
}

.header {
  overflow: hidden;
  background-color: #2c2c2c;
  padding: 20px 10px;
}

.header a {
  float: left;
  color: #ddd;
  text-align: center;
  padding: 12px;
  text-decoration: none;
  font-size: 12px; 
  line-height: 15px;
  border-radius: 4px;
}

.header a.logo {
  font-size: 25px;
  font-weight: bold;
  color: #ddd;
}

.header a:hover {
  background-color: rgba(221, 221, 221, 0.187);
  color: black;
}

.header a.active {
  background-color: rgb(64, 82, 100);
  color: white;
}

.header-right {
  float: right;
}

@media screen and (max-width: 500px) {
  .header a {
    float: none;
    display: block;
    text-align: left;
  }
  
  .header-right {
    float: none;
  }
    
}

    .wrapper {
        /*
            text-align: center;
            justify-content: center;
            display: block;
            margin-left: auto;
            margin-right: auto;
            max-width: 300px;
            */
    }

    /* SWITCH */
    :root {
            --light: #d8dbe0;
            --dark: #28292c;
            --link: rgb(27, 129, 112);
            --link-hover: rgb(24, 94, 82);
        }
    
    .toggle-switch {
            position: relative;
            width: 200px;
            display: inline-block;
        }
        
        label {
            position: absolute;
            width: 100px;
            height: 50px;
            background-color: var(--dark);
            border-radius: 25px;
            cursor: pointer;
        }
        
        input {
            position: relative;
            display: none;
        }
        
        .slider {
            position: absolute;
            width: 100px;
            height: 50px;
            border-radius: 25px;
            transition: 0.3s;
        }
        
        input:checked~.slider {
            background-color: var(--light);
        }
        
        .slider::before {
            content: "";
            position: absolute;
            top: 7px;
            left: 8px;
            width: 35px;
            height: 35px;
            border-radius: 50%;
            box-shadow: inset 15px -3px 0px 0px var(--light);
            background-color: var(--dark);
            transition: 0.3s;
        }
        
        input:checked~.slider::before {
            transform: translateX(45px);
            background-color: var(--dark);
            box-shadow: none;
        }
        
        .switch-label {
            position: relative;
        }
        
        .center {
            margin-left: auto;
            margin-right: auto;
            /*background-color: #060606;*/
        }
        
        .tr-main {
            height: 70px;
        }
        
        .td-first {
            width: 120px;
            position: relative;
            top: -25px;
        }
        
        .td-second {
            padding-left: 60px;
            width: 120px;
            position: relative;
            top: -25px;
        }
        
        .name-title {
            font-size: 1.4em;
        }
        
        input[type=text] {
            width: 100%;
            padding: 12px 20px;
            margin: 8px 0;
            box-sizing: border-box;
        }
</style>
</head>
<body>
<div class="header">
  <a href="/" class="logo">The Crow's Nest Switch</a>
  <div class="header-right">
    <a class="active" href="/">Home</a>
    <a href="/edit">Edit</a>
  </div>
</div>
<div class="wrapper">
)rawliteral";

const char index_html_footer[] PROGMEM = R"rawliteral(
  </div>
  <script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?relay="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?relay="+element.id+"&state=0", true); }
  xhr.send();
}</script>
</body>
</html>
  )rawliteral";


const char edit_html_header[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body {
            margin: 0;
            font-family: Arial, Helvetica, sans-serif;
            background-color: #1a1a1a;
            color: #d8dbe0;
        }
        
        html {
            font-family: Arial;
        }
        
        h2 {
            text-align: center;
            font-size: 2.0rem;
        }
        
        .header {
            overflow: hidden;
            background-color: #2c2c2c;
            padding: 20px 10px;
        }
        
        .header a {
            float: left;
            color: #ddd;
            text-align: center;
            padding: 12px;
            text-decoration: none;
            font-size: 12px;
            line-height: 15px;
            border-radius: 4px;
        }
        
        .header a.logo {
            font-size: 25px;
            font-weight: bold;
            color: #ddd;
        }
        
        .header a:hover {
            background-color: rgba(221, 221, 221, 0.187);
            color: black;
        }
        
        .header a.active {
            background-color: rgb(64, 82, 100);
            color: white;
        }
        
        .header-right {
            float: right;
        }
        
        @media screen and (max-width: 500px) {
            .header a {
                float: none;
                display: block;
                text-align: left;
            }
            .header-right {
                float: none;
            }
        }
        
        .wrapper {
            text-align: center;
            justify-content: center;
            display: block;
            margin-left: auto;
            margin-right: auto;
            max-width: 300px;
        }
        
        input[type=text],
        select {
            width: 100%;
            padding: 12px 20px;
            margin: 8px 0;
            display: inline-block;
            border: 1px solid #ccc;
            border-radius: 4px;
            box-sizing: border-box;
        }
        
        input[type=submit] {
            width: 100%;
            background-color: #2e2d31;
            color: white;
            padding: 14px 20px;
            margin: 8px 0;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        
        input[type=submit]:hover {
            background-color: #45a049;
        }
    </style>
</head>

<body>
    <div class="header">
        <a href="/" class="logo">The Crow's Nest Switch</a>
        <div class="header-right">
            <a href="/">Home</a>
            <a class="active" href="/edit">Edit</a>
        </div>
    </div>
    <div class="wrapper">
        <h2>Rename Relays</h2>
    )rawliteral";

const char edit_html_footer[] PROGMEM = R"rawliteral(
</body>
</html>
    )rawliteral";