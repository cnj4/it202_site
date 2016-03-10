DROP TABLE IF EXISTS users;
create table users
    (
        userID INT(16) primary key auto_increment,
        username varchar(32),
        userPW varchar(64),
        firstLogin datetime,
        lastLogin datetime
    );
