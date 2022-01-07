DROP TABLE IF EXISTS PartsUsed;

-- Parts Used for invoice 1
INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (1, 1, 1);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (2, 1, 4);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (3, 1, 150);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (5, 1, 15);

-- Parts Used for invoice 2
INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (1, 2, 2);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (2, 2, 23);

-- Parts Used for invoice 3
INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (4, 3, 1);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (2, 3, 4);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (1, 3, 150);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (3, 3, 15);

-- Parts used for invoice 4

-- Parts used for invoice 5
INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (3, 5, 1);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (4, 5, 4);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (5, 5, 150);

INSERT INTO PartsUsed(pid, po, quantity)
  VALUES (1, 5, 15);
