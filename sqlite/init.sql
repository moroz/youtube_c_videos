drop table if exists products;

create table products (
  id uuid primary key,
  title text not null,
  slug text not null unique,
  description text,
  base_price numeric not null default 0.0,
  inserted_at bigint not null default (unixepoch()),
  updated_at bigint not null default (unixepoch())
);
