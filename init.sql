DROP TABLE IF EXISTS users, messages;
create table users
    (
        userID INT(16) primary key auto_increment,
        username varchar(32),
        userPW varchar(64),
        firstLogin datetime,
        lastLogin datetime
    );
create table messages
    (
        messageID INT(16) primary key auto_increment,
        timestamp datetime,
        user varchar(32),
        message varchar(255)
    );
