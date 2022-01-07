
CREATE TABLE Clients(
  cid NUMBER(8) PRIMARY KEY,
  first_name VARCHAR(42) NOT NULL,
  last_name VARCHAR(42) NOT NULL,
  email VARCHAR(42),
  address VARCHAR(256),
  phone_number VARCHAR(10)
);

CREATE TABLE Parts(
  pid NUMBER(12) PRIMARY KEY,
  description VARCHAR(256),
  unit VARCHAR(4) NOT NULL,
  wholesale NUMBER(6, 2) NOT NULL CHECK (wholesale > 0),
  retail NUMBER(6, 2) NOT NULL,
  CONSTRAINT retail CHECK (retail >= wholesale)
);

CREATE TABLE Employee(
  eid NUMBER(5) PRIMARY KEY,
  status VARCHAR(8) NOT NULL,
  first_name VARCHAR(42) NOT NULL,
  last_name VARCHAR(42) NOT NULL,
  rate NUMBER(5, 2) NOT NULL CHECK (rate > 0),
  CHECK (status IN ('active', 'inactive', 'leave', 'terminated'))
);

-- Employees can have multiple jobs within the company at the same time
CREATE TABLE Jobs(
  eid NUMBER (5) REFERENCES Employees,
  position VARCHAR(42) NOT NULL,
  CHECK (position IN ('tecnician', 'admin')),
  PRIMARY KEY (eid, position)
);

CREATE TABLE Invoices(
  po NUMBER(24) PRIMARY KEY,
  client NUMBER(8) REFERENCES Clients,
  status VARCHAR(12) NOT NULL,
  issued DATE NOT NULL,
  workStart DATE,
  workEnd DATE,
  description VARCHAR(3000),
  CHECK (status IN ('scheduled', 'active', 'sent', 'completed')),
  CHECK (workStart <= workEnd)
);

CREATE TABLE ClockInOut(
  clockIn TIMESTAMP(6),
  startLunch TIMESTAMP(6),
  endLunch TIMESTAMP(6),
  clockOut TIMESTAMP(6) NOT NULL,
  job NUMBER(24) REFERENCES Invoices,
  eid NUMBER(5) REFERENCES Employee,
  PRIMARY KEY (clockIn, eid)
);

CREATE TABLE PartsUsed(
  pid NUMBER(12) REFERENCES Parts NOT NULL,
  po NUMBER(24) REFERENCES Invoices NOT NULL,
  quantity NUMBER(12) DEFAULT 0,
  PRIMARY KEY (pid, po),
  CHECK (quantity >= 0)
);
