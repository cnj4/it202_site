#!/usr/bin/php
<?php
require_once("error.php.inc");

class clientDB
{
//TODO: Change all errors to log insted of echo
    private $db;
    private $salt;
    private $logger;

    public function __construct($iniFile)
    {
        $ini = parse_ini_file($iniFile, true);
        $logger = new errorLogger("/var/log/it202.log");

        $this->db = new mysqli(
            $ini['loginDB']['host'],
            $ini['loginDB']['username'],
            $ini['loginDB']['password'],
            $ini['loginDB']['db']);
        $this->salt = $ini['loginDB']['salt'];

        if ( $this->db->connect_errno > 0 )
        {
            $this->logger->log(__file__.__line__."failed to connect to database re: ".$db->connect_error);
            exit(0);
        }

    }

    public function __destruct()
    {
        $this->db->close();
    }

    public function getClientId($name)
    {
        $query = $this->db->real_escape_string("select * from clients where clientName='$name';");
        $result = $this->db->query($query);

        if(!$result)
        {
            $this->logger->log("error with results: ".$this->db->error);
            return 0;
        }
        $client = $result->fetch_assoc();
        if(isset($client['clientId']))
        {
            return $client['clientId'];
        }

    }

    public function validateClient($name, $pw)
    {

        if($this->getClientId($name) == 0)
        {
            $this->logger->log("User $name does not exist");
            return false;
        }
        $query = $this->db->real_escape_string("select * from clients where clientName='$name';");
        $result = $this->db->query($query);
        if(!$result){
            $this->logger->log("error with results: ".$this->db->error);
            return false;
        }

        $client = $result->fetch_assoc();
        if(isset($client['clientPW']) && $client['clientPW'] == $this->saltPassword($pw))
        {
            return true;
        }

        return false;

    }

    private function saltPassword($password, $salt)
    {
        return $this->db->real_escape_string(sha1($password.$salt));
    }

    public function addNewClient($name, $pw)
    {
        if ($this->getClientId($name) != 0){
            $this->logger->log("User $name already exists".PHP_EOL);
            return;
        }
        $now = date("Y-m-d h:i:s", time());
        $addQuery = $this->db->real_escape_string("insert into clients (clientName,clientPW,firstLogin,lastLogin) values('$name','$this->saltPassword($pw)','$now','$now');");
        $this->db->query($addQuery);
    }
}

?>
