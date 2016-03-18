<?php
require_once("userDB.php.inc");

$request = $_POST['request'];
$result = "Something went wrong.";

switch($request)
{
case "register":
    $name = $_POST['username'];
    $password = $_POST['password'];
    $db = new userDB("connect.ini");
    $db->addNewUser($name,$password);
    $result = "New user $name created!";
    $link = "return";
    break;

case "login":
    $name = $_POST['username'];
    $password = $_POST['password'];
    $db = new userDB("connect.ini");
    if ($db->validateUser($name,$password))
    {
        $result = "Login Successful!";
        $link = "continue";
        $login = $name;
    }
    else
    {
        $result = "Invalid Login!";
        $link = "return";
    }
    break;
}

echo $result.PHP_EOL;

switch($link)
{
case "return":
    //TODO:HTML return to login link
    echo "<a href=\"index.html\">return to login</a>".PHP_EOL;
    echo "Return Link goes here".PHP_EOL;
    break;

case "contirnue":
    //TODO:HTML continue to chat link
    echo "<a href=\"chat.php\">Continue to chat</a>"..PHP_EOL;
    echo "Continue Link goes here".PHP_EOL;
    break;
}
?>
