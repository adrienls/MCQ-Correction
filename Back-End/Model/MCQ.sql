-- phpMyAdmin SQL Dump
-- version 4.6.6deb5
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 20, 2019 at 11:34 AM
-- Server version: 10.3.15-MariaDB-1
-- PHP Version: 7.3.4-2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `MCQ`
--

-- --------------------------------------------------------

--
-- Table structure for table `answer`
--

CREATE TABLE `answer` (
  `id_answer` int(11) NOT NULL,
  `id_student` int(11) NOT NULL,
  `id_question` int(11) NOT NULL,
  `value` varchar(24) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `correction`
--

CREATE TABLE `correction` (
  `id_correction` int(11) NOT NULL,
  `id_question` int(11) NOT NULL,
  `value` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `examination`
--

CREATE TABLE `examination` (
  `id_examination` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `date` date NOT NULL,
  `id_promotion` int(11) NOT NULL,
  `login_teacher` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `promotion`
--

CREATE TABLE `promotion` (
  `id_promotion` int(11) NOT NULL,
  `name` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `promotion`
--

INSERT INTO `promotion` (`id_promotion`, `name`) VALUES
(1, 'CIR'),
(2, 'CSI');

-- --------------------------------------------------------

--
-- Table structure for table `question`
--

CREATE TABLE `question` (
  `id_question` int(11) NOT NULL,
  `id_examination` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `scale`
--

CREATE TABLE `scale` (
  `id_scale` int(11) NOT NULL,
  `id_examination` int(11) NOT NULL,
  `bonus` float NOT NULL,
  `malus` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `student`
--

CREATE TABLE `student` (
  `id_student` int(11) NOT NULL,
  `id_promotion` int(11) NOT NULL,
  `firstname` varchar(255) NOT NULL,
  `lastname` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `student`
--

INSERT INTO `student` (`id_student`, `id_promotion`, `firstname`, `lastname`) VALUES
(1, 1, 'Jean', 'Moulin'),
(2, 1, 'Lyne', 'Moulin'),
(3, 1, 'Michel', 'Gateu'),
(4, 1, 'Bertrand', 'Comlin'),
(5, 1, 'Gérard', 'Lila'),
(6, 1, 'Benoit', 'Poelvoorde'),
(7, 1, 'Francis', 'Humort'),
(8, 1, 'Arnaud', 'Tsamere'),
(9, 1, 'Harold', 'Eleve'),
(10, 1, 'Baptises', 'Toyota'),
(11, 1, 'Robin', 'Moulin'),
(12, 1, 'Renaud', 'Megan'),
(13, 1, 'Robtrois', 'Frog'),
(14, 1, 'Bibi', 'Phileas'),
(15, 1, 'Adrien', 'Trousse'),
(16, 1, 'Mélina', 'Lubro'),
(17, 1, 'Quentin', 'Mastic'),
(18, 1, 'Jérémy', 'Perdro'),
(19, 1, 'Quentin', 'Jaquet'),
(20, 1, 'Antoine', 'Mouf'),
(21, 2, 'Arthur', 'Machine'),
(22, 2, 'Kevin', 'Duchateau'),
(23, 2, 'Dylan', 'Onor'),
(24, 2, 'Ryan', 'Desailly'),
(25, 2, 'Tim', 'Dugast'),
(26, 2, 'Théo', 'Martin'),
(27, 2, 'Mickael', 'Rouge'),
(28, 2, 'Isabelle', 'Branche'),
(29, 2, 'Marie', 'Blonde'),
(30, 2, 'Eugénie', 'Audoire'),
(31, 2, 'Cloé', 'Arbre'),
(32, 2, 'Tod', 'Guerineau'),
(33, 2, 'Yoshi', 'Mouton'),
(34, 2, 'Juliette', 'Villemin'),
(35, 2, 'Elodie', 'Librairie'),
(36, 2, 'Annette', 'Verre'),
(37, 2, 'Laurane', 'Bouchon'),
(38, 2, 'Clémentine', 'Beach'),
(39, 2, 'Maureen', 'Sport'),
(40, 2, 'Caroline', 'Uno');

-- --------------------------------------------------------

--
-- Table structure for table `teacher`
--

CREATE TABLE `teacher` (
  `login` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `token` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `answer`
--
ALTER TABLE `answer`
  ADD PRIMARY KEY (`id_answer`),
  ADD KEY `answer_id_student` (`id_student`),
  ADD KEY `answer_id_question` (`id_question`);

--
-- Indexes for table `correction`
--
ALTER TABLE `correction`
  ADD PRIMARY KEY (`id_correction`),
  ADD KEY `correction_id_question` (`id_question`);

--
-- Indexes for table `examination`
--
ALTER TABLE `examination`
  ADD PRIMARY KEY (`id_examination`),
  ADD KEY `examination_id_promotion` (`id_promotion`),
  ADD KEY `examination_login_teacher` (`login_teacher`);

--
-- Indexes for table `promotion`
--
ALTER TABLE `promotion`
  ADD PRIMARY KEY (`id_promotion`),
  ADD UNIQUE KEY `name` (`name`);

--
-- Indexes for table `question`
--
ALTER TABLE `question`
  ADD PRIMARY KEY (`id_question`),
  ADD KEY `question_id_examination` (`id_examination`);

--
-- Indexes for table `scale`
--
ALTER TABLE `scale`
  ADD PRIMARY KEY (`id_scale`),
  ADD KEY `scale_id_examination` (`id_examination`);

--
-- Indexes for table `student`
--
ALTER TABLE `student`
  ADD PRIMARY KEY (`id_student`),
  ADD KEY `student_id_promotion` (`id_promotion`);

--
-- Indexes for table `teacher`
--
ALTER TABLE `teacher`
  ADD PRIMARY KEY (`login`),
  ADD UNIQUE KEY `token` (`token`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `answer`
--
ALTER TABLE `answer`
  MODIFY `id_answer` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `correction`
--
ALTER TABLE `correction`
  MODIFY `id_correction` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `examination`
--
ALTER TABLE `examination`
  MODIFY `id_examination` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `promotion`
--
ALTER TABLE `promotion`
  MODIFY `id_promotion` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
--
-- AUTO_INCREMENT for table `question`
--
ALTER TABLE `question`
  MODIFY `id_question` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `scale`
--
ALTER TABLE `scale`
  MODIFY `id_scale` int(11) NOT NULL AUTO_INCREMENT;
--
-- AUTO_INCREMENT for table `student`
--
ALTER TABLE `student`
  MODIFY `id_student` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=41;
--
-- Constraints for dumped tables
--

--
-- Constraints for table `answer`
--
ALTER TABLE `answer`
  ADD CONSTRAINT `answer_id_question` FOREIGN KEY (`id_question`) REFERENCES `question` (`id_question`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `answer_id_student` FOREIGN KEY (`id_student`) REFERENCES `student` (`id_student`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `correction`
--
ALTER TABLE `correction`
  ADD CONSTRAINT `correction_id_question` FOREIGN KEY (`id_question`) REFERENCES `question` (`id_question`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `examination`
--
ALTER TABLE `examination`
  ADD CONSTRAINT `examination_id_promotion` FOREIGN KEY (`id_promotion`) REFERENCES `promotion` (`id_promotion`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `examination_login_teacher` FOREIGN KEY (`login_teacher`) REFERENCES `teacher` (`login`) ON DELETE NO ACTION ON UPDATE CASCADE;

--
-- Constraints for table `question`
--
ALTER TABLE `question`
  ADD CONSTRAINT `question_id_examination` FOREIGN KEY (`id_examination`) REFERENCES `examination` (`id_examination`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `scale`
--
ALTER TABLE `scale`
  ADD CONSTRAINT `scale_id_examination` FOREIGN KEY (`id_examination`) REFERENCES `examination` (`id_examination`) ON DELETE CASCADE ON UPDATE CASCADE;

--
-- Constraints for table `student`
--
ALTER TABLE `student`
  ADD CONSTRAINT `student_id_promotion` FOREIGN KEY (`id_promotion`) REFERENCES `promotion` (`id_promotion`) ON DELETE CASCADE ON UPDATE CASCADE;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
