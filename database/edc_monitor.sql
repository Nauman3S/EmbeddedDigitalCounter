-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Host: srv-captain--vb-mysqldb-db:3306
-- Generation Time: Apr 02, 2021 at 06:21 AM
-- Server version: 5.7.33
-- PHP Version: 7.4.16

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `edc_monitor`
--

-- --------------------------------------------------------

--
-- Table structure for table `data`
--

CREATE TABLE `data` (
  `ID` int(11) NOT NULL,
  `Timestamp` text NOT NULL,
  `PlayerID` text NOT NULL,
  `TMIN30` text NOT NULL,
  `TMOUT30` text NOT NULL,
  `TMIND` text NOT NULL,
  `TMOUTD` text NOT NULL,
  `ActiveStatus` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `data`
--

INSERT INTO `data` (`ID`, `Timestamp`, `PlayerID`, `TMIN30`, `TMOUT30`, `TMIND`, `TMOUTD`, `ActiveStatus`) VALUES
(1, '2/87/32', '1252343128', '4', '12', '12', '4', '1'),
(2, '33/2/1', '12543121233', '1', '2', '3', '44', '0'),
(3, '9/54/2', '61243812331', '3', '5', '23', '41', '0'),
(4, 'undefined', '88565413851', 'undefined', 'undefined', 'undefined', 'undefined', '0'),
(5, '1', '32176198412', '/', '2', '/', '2', '0'),
(6, '1', '293763984126', '/', '2', '/', '2', '0'),
(7, '2/2/3', '897614413332', '4', '66', '234', '12', '0');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE `user` (
  `company` text NOT NULL,
  `username` text NOT NULL,
  `email` text NOT NULL,
  `firstname` text NOT NULL,
  `lastname` text NOT NULL,
  `address` text NOT NULL,
  `city` text NOT NULL,
  `country` text NOT NULL,
  `postalcode` text NOT NULL,
  `aboutme` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`company`, `username`, `email`, `firstname`, `lastname`, `address`, `city`, `country`, `postalcode`, `aboutme`) VALUES
('NoCompany', 'EricT', 'Eric@Email.com', 'Eric', 'Thompson', 'Street 3 NYC Den', 'NYC', 'US', '10554', 'Nothing special!');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `data`
--
ALTER TABLE `data`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `data`
--
ALTER TABLE `data`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=8;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
