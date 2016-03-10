#!/usr/bin/php
<?php
require_once("clientDB.php.inc");

$command = $argv[1];

switch($command)
{
case 'register':
    $name = $argv[2];
    $password = $argv[3];
    $db = new clientDB();
    $db->addNewClient($name,$password);
    break;
case 'login':
    $name = $argv[2];
    $password = $argv[3];
    $db = new clientDB();
    if ($db->validateClient($name,$password))
    {
        echo "Login Successful!".PHP_EOL;
    }
    else
    {
        echo "Invalid Login!".PHP_EOL;
    }
    break;
default:
    echo "Usage: ".PHP_EOL."[login|register] <username> <password>".PHP_EOL;
}

?>
