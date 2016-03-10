#!/usr/bin/php
<?php
class clientDB
{

    private $db;
    private $salt;

    public function __construct($iniFile)
    {
        $ini = parse_ini_file($iniFile, true);

        $this->db = new mysqli(
            $ini['loginDB']['host'],
            $ini['loginDB']['username'],
            $ini['loginDB']['password'],
            $ini['loginDB']['db']);
        $this->salt = $ini['loginDB']['salt'];

        if ( $this->db->connect_errno > 0 )
        {
            echo __file__.__line__."failed to connect to database re: ".$db->connect_error.PHP_EOL;
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
            echo "error with results: ".$this->db->error.PHP_EOL;
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
            echo "User $name does not exist".PHP_EOL;
            return false;
        }
        $query = $this->db->real_escape_string("select * from clients where clientName='$name';");
        $result = $this->db->query($query);
        if(!$result){
            echo "error with results: ".$this->db->error.PHP_EOL;
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
            echo "User $name already exists".PHP_EOL;
            return;
        }
        $now = date("Y-m-d h:i:s", time());
        $addQuery = $this->db->real_escape_string("insert into clients (clientName,clientPW,firstLogin,lastLogin) values('$name','$this->saltPassword($pw)','$now','$now');");
        $this->db->query($addQuery);
    }
}

?>
