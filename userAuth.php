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
    break;
case 'login':
    $name = $_POST['username'];
    $password = $_POST['password'];
    $db = new userDB("connect.ini");
    if ($db->validateUser($name,$password))
    {
        $result = "Login Successful!";
    }
    else
    {
        $result = "Invalid Login!";
    }
    break;
}

echo $result.PHP_EOL;

?>
