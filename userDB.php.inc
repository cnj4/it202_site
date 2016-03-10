<?php
require_once("error.php.inc");

class userDB
{
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

    public function getUserId($name)
    {
        $name = $this->db->real_escape_string($name);
        $query = "select * from users where username='$name';";
        $result = $this->db->query($query);

        if(!$result)
        {
            $this->logger->log("error with results: ");
            return 0;
        }
        $user = $result->fetch_assoc();
        if(isset($user['userID']))
        {
            return $user['userID'];
        }

    }

    public function validateUser($name, $pw)
    {

        if($this->getUserId($name) == 0)
        {
            $this->logger->log("User $name does not exist");
            return false;
        }
        $name = $this->db->real_escape_string($name);
        $query = "select * from users where username='$name';";
        $result = $this->db->query($query);
        if(!$result){
            $this->logger->log("error with results: ".$this->db->error);
            return false;
        }

        $user = $result->fetch_assoc();
        if(isset($user['userPW']) && $user['userPW'] == $this->saltPassword($pw,$this->salt))
        {
            return true;
        }

        return false;

    }

    private function saltPassword($password, $salt)
    {
        return $this->db->real_escape_string(sha1($password.$salt));
    }

    public function addNewUser($name, $password)
    {
        $name = $this->db->real_escape_string($name);
        $pw = $this->saltPassword($password, $this->salt);
        $now = date("Y-m-d h:i:s", time());
        $addQuery = "insert into users (username,userPW,firstLogin,lastLogin) values('$name','$pw','$now','$now');";
        $this->db->query($addQuery);
    }
}

?>
