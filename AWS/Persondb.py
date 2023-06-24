CREATE DATABASE Persondb;
USE Persondb;

CREATE TABLE Power (
    Colour varchar(255),
    Vin varchar(255),
    Vout varchar(255),
    Iout varchar(255),
    Duty varchar(255)
);

INSERT INTO Power VALUES ('Yellow', '2.5', '3.3', '1.5mA', '88%');
INSERT INTO Power VALUES ('Red', '2.5', '3.3', '1.5mA', '88%');
INSERT INTO Power VALUES ('Blue', '2.5', '3.3', '1.5mA', '88%');

# CREATE TABLE Position (
#     Xaxis varchar(255),
#     Yaxis varchar(255)
# );

# INSERT INTO Position (Xaxis, Yaxis) VALUES ('0', '0');

CREATE TABLE Angle (
    ID int,
    Dif1 varchar(255),
    Dif2 varchar(255)
);

INSERT INTO Angle (ID, Dif1, Dif2) VALUES (1, '0', '0');


CREATE TABLE BeaconCoordinates (
    BeaconColour varchar(255),
    TopXaxis varchar(255),
    TopYaxis varchar(255),
    BottomXaxis varchar(255),
    BottomYaxis varchar(255)
);
INSERT INTO BeaconCoordinates VALUES ('red', '100', '50', '150', '100');
INSERT INTO BeaconCoordinates VALUES ('yellow', '250', '100', '300', '150');
INSERT INTO BeaconCoordinates VALUES ('blue', '200', '80', '250', '130');


CREATE TABLE Persons (
    PersonID int,
    LastName varchar(255),
    FirstName varchar(255),
    Year varchar(255),
    Task varchar(255)
);
INSERT INTO Persons VALUES (1, 'Ethan', 'Chen', 'Imperial College London', 'London');
