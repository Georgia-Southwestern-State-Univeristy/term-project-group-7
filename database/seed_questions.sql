-- ========================
-- 6TH GRADE
-- ========================

-- ADDITION (6th)
INSERT INTO questions (topic, grade_level, difficulty, question_text, correct_answer, explanation) VALUES
('addition',6,'easy','125 + 340',465,'Add ones, tens, hundreds'),
('addition',6,'easy','78 + 56',134,'Add digits column-wise'),
('addition',6,'medium','456 + 789',1245,'Carry over values'),
('addition',6,'medium','999 + 1',1000,'Edge case addition'),
('addition',6,'hard','2345 + 6789',9134,'Multi-digit addition'),
('addition',6,'easy','300 + 200',500,'Simple addition'),
('addition',6,'medium','123 + 987',1110,'Carry across digits'),
('addition',6,'hard','4567 + 1234',5801,'Multi-digit addition'),
('addition',6,'easy','50 + 25',75,'Basic addition'),
('addition',6,'medium','678 + 432',1110,'Column addition');

-- SUBTRACTION (6th)
INSERT INTO questions VALUES
(NULL,'subtraction',6,'easy','500 - 200',300,'Subtract hundreds'),
(NULL,'subtraction',6,'easy','90 - 45',45,'Simple subtraction'),
(NULL,'subtraction',6,'medium','456 - 123',333,'Column subtraction'),
(NULL,'subtraction',6,'medium','1000 - 1',999,'Borrowing'),
(NULL,'subtraction',6,'hard','3456 - 1234',2222,'Multi-digit subtraction'),
(NULL,'subtraction',6,'easy','75 - 25',50,'Basic subtraction'),
(NULL,'subtraction',6,'medium','876 - 543',333,'Column subtraction'),
(NULL,'subtraction',6,'hard','9999 - 8888',1111,'Large subtraction'),
(NULL,'subtraction',6,'easy','60 - 30',30,'Simple subtraction'),
(NULL,'subtraction',6,'medium','700 - 350',350,'Half subtraction');

-- MULTIPLICATION (6th)
INSERT INTO questions VALUES
(NULL,'multiplication',6,'easy','5 * 6',30,'Basic multiplication'),
(NULL,'multiplication',6,'easy','7 * 8',56,'Times table'),
(NULL,'multiplication',6,'medium','12 * 12',144,'Square number'),
(NULL,'multiplication',6,'medium','15 * 10',150,'Multiply by 10'),
(NULL,'multiplication',6,'hard','123 * 4',492,'Multi-digit'),
(NULL,'multiplication',6,'easy','9 * 9',81,'Times table'),
(NULL,'multiplication',6,'medium','25 * 4',100,'Quarter logic'),
(NULL,'multiplication',6,'hard','111 * 11',1221,'Pattern multiplication'),
(NULL,'multiplication',6,'easy','6 * 7',42,'Basic'),
(NULL,'multiplication',6,'medium','14 * 3',42,'Multiply');

-- DIVISION (6th)
INSERT INTO questions VALUES
(NULL,'division',6,'easy','30 / 5',6,'Basic division'),
(NULL,'division',6,'easy','56 / 8',7,'Times table inverse'),
(NULL,'division',6,'medium','144 / 12',12,'Division'),
(NULL,'division',6,'medium','100 / 10',10,'Divide by 10'),
(NULL,'division',6,'hard','492 / 4',123,'Inverse multiplication'),
(NULL,'division',6,'easy','81 / 9',9,'Times table'),
(NULL,'division',6,'medium','100 / 4',25,'Division'),
(NULL,'division',6,'hard','121 / 11',11,'Pattern'),
(NULL,'division',6,'easy','42 / 7',6,'Basic'),
(NULL,'division',6,'medium','84 / 6',14,'Division');

-- ========================
-- 7TH GRADE (slightly harder)
-- ========================

-- ADDITION (7th)
INSERT INTO questions VALUES
(NULL,'addition',7,'medium','2345 + 6789',9134,'Large numbers'),
(NULL,'addition',7,'hard','9999 + 9999',19998,'Carry over all digits'),
(NULL,'addition',7,'medium','1234 + 5678',6912,'Addition'),
(NULL,'addition',7,'hard','8765 + 4321',13086,'Addition'),
(NULL,'addition',7,'medium','555 + 555',1110,'Pattern'),
(NULL,'addition',7,'hard','7890 + 1234',9124,'Addition'),
(NULL,'addition',7,'medium','321 + 654',975,'Addition'),
(NULL,'addition',7,'hard','8888 + 1111',9999,'Addition'),
(NULL,'addition',7,'medium','456 + 654',1110,'Addition'),
(NULL,'addition',7,'hard','999 + 999',1998,'Addition');

-- SUBTRACTION (7th)
INSERT INTO questions VALUES
(NULL,'subtraction',7,'medium','5000 - 1234',3766,'Borrowing'),
(NULL,'subtraction',7,'hard','9999 - 5555',4444,'Large subtraction'),
(NULL,'subtraction',7,'medium','8765 - 4321',4444,'Subtract'),
(NULL,'subtraction',7,'hard','10000 - 1',9999,'Edge case'),
(NULL,'subtraction',7,'medium','3456 - 1111',2345,'Subtract'),
(NULL,'subtraction',7,'hard','8000 - 6789',1211,'Borrowing'),
(NULL,'subtraction',7,'medium','777 - 333',444,'Subtract'),
(NULL,'subtraction',7,'hard','6543 - 3210',3333,'Subtract'),
(NULL,'subtraction',7,'medium','900 - 450',450,'Subtract'),
(NULL,'subtraction',7,'hard','4321 - 1234',3087,'Subtract');

-- MULTIPLICATION (7th)
INSERT INTO questions VALUES
(NULL,'multiplication',7,'medium','23 * 12',276,'Multiply'),
(NULL,'multiplication',7,'hard','123 * 45',5535,'Multi-digit'),
(NULL,'multiplication',7,'medium','34 * 10',340,'Multiply'),
(NULL,'multiplication',7,'hard','111 * 111',12321,'Pattern'),
(NULL,'multiplication',7,'medium','56 * 2',112,'Multiply'),
(NULL,'multiplication',7,'hard','222 * 22',4884,'Multiply'),
(NULL,'multiplication',7,'medium','75 * 4',300,'Multiply'),
(NULL,'multiplication',7,'hard','321 * 12',3852,'Multiply'),
(NULL,'multiplication',7,'medium','99 * 2',198,'Multiply'),
(NULL,'multiplication',7,'hard','444 * 11',4884,'Multiply');

-- DIVISION (7th)
INSERT INTO questions VALUES
(NULL,'division',7,'medium','276 / 12',23,'Divide'),
(NULL,'division',7,'hard','5535 / 45',123,'Inverse'),
(NULL,'division',7,'medium','340 / 10',34,'Divide'),
(NULL,'division',7,'hard','12321 / 111',111,'Pattern'),
(NULL,'division',7,'medium','112 / 2',56,'Divide'),
(NULL,'division',7,'hard','4884 / 22',222,'Divide'),
(NULL,'division',7,'medium','300 / 4',75,'Divide'),
(NULL,'division',7,'hard','3852 / 12',321,'Divide'),
(NULL,'division',7,'medium','198 / 2',99,'Divide'),
(NULL,'division',7,'hard','4884 / 11',444,'Divide');

-- ========================
-- 8TH GRADE (harder logic)
-- ========================

-- ADDITION
INSERT INTO questions VALUES
(NULL,'addition',8,'hard','12345 + 67890',80235,'Large addition'),
(NULL,'addition',8,'hard','99999 + 1',100000,'Carry all'),
(NULL,'addition',8,'hard','88888 + 22222',111110,'Addition'),
(NULL,'addition',8,'medium','4567 + 7654',12221,'Addition'),
(NULL,'addition',8,'hard','77777 + 33333',111110,'Addition'),
(NULL,'addition',8,'medium','1357 + 2468',3825,'Addition'),
(NULL,'addition',8,'hard','98765 + 43210',141975,'Addition'),
(NULL,'addition',8,'medium','1111 + 9999',11110,'Addition'),
(NULL,'addition',8,'hard','50000 + 50000',100000,'Addition'),
(NULL,'addition',8,'medium','6789 + 1234',8023,'Addition');

-- SUBTRACTION
INSERT INTO questions VALUES
(NULL,'subtraction',8,'hard','100000 - 1',99999,'Edge'),
(NULL,'subtraction',8,'hard','99999 - 12345',87654,'Subtract'),
(NULL,'subtraction',8,'medium','7654 - 1234',6420,'Subtract'),
(NULL,'subtraction',8,'hard','88888 - 44444',44444,'Subtract'),
(NULL,'subtraction',8,'medium','5432 - 1111',4321,'Subtract'),
(NULL,'subtraction',8,'hard','77777 - 33333',44444,'Subtract'),
(NULL,'subtraction',8,'medium','9000 - 4500',4500,'Subtract'),
(NULL,'subtraction',8,'hard','12345 - 5432',6913,'Subtract'),
(NULL,'subtraction',8,'medium','8000 - 2000',6000,'Subtract'),
(NULL,'subtraction',8,'hard','10000 - 9999',1,'Edge');

-- MULTIPLICATION
INSERT INTO questions VALUES
(NULL,'multiplication',8,'hard','123 * 123',15129,'Square'),
(NULL,'multiplication',8,'hard','999 * 999',998001,'Square'),
(NULL,'multiplication',8,'medium','45 * 20',900,'Multiply'),
(NULL,'multiplication',8,'hard','321 * 321',103041,'Square'),
(NULL,'multiplication',8,'medium','75 * 8',600,'Multiply'),
(NULL,'multiplication',8,'hard','111 * 222',24642,'Multiply'),
(NULL,'multiplication',8,'medium','60 * 7',420,'Multiply'),
(NULL,'multiplication',8,'hard','432 * 123',53136,'Multiply'),
(NULL,'multiplication',8,'medium','90 * 9',810,'Multiply'),
(NULL,'multiplication',8,'hard','555 * 555',308025,'Square');

-- DIVISION
INSERT INTO questions VALUES
(NULL,'division',8,'hard','15129 / 123',123,'Inverse'),
(NULL,'division',8,'hard','998001 / 999',999,'Inverse'),
(NULL,'division',8,'medium','900 / 20',45,'Divide'),
(NULL,'division',8,'hard','103041 / 321',321,'Inverse'),
(NULL,'division',8,'medium','600 / 8',75,'Divide'),
(NULL,'division',8,'hard','24642 / 222',111,'Divide'),
(NULL,'division',8,'medium','420 / 7',60,'Divide'),
(NULL,'division',8,'hard','53136 / 123',432,'Divide'),
(NULL,'division',8,'medium','810 / 9',90,'Divide'),
(NULL,'division',8,'hard','308025 / 555',555,'Divide');