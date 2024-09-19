CREATE EXTENSION CITEXT;
-- #TODO: Add commentary history
-- #TODO: Add translation history





-- The enum column will indicates whether occurances of a tag within a post should be counted or not.
CREATE TABLE public.tags (
	id SERIAL PRIMARY KEY,
	name CITEXT UNIQUE NOT NULL,
	type INTEGER NOT NULL DEFAULT 0,
	enum BOOLEAN NOT NULL DEFAULT FALSE,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





-- #TODO: Refactor this ASAP! This must be capable of storing tag "triplets"
CREATE TABLE public.aliases (
	alias CITEXT UNIQUE NOT NULL,
	tag_id INTEGER NOT NULL
);

ALTER TABLE public.aliases ADD FOREIGN KEY (tag_id) REFERENCES public.tags (id) ON DELETE RESTRICT;





-- [implicator]{ +[implicatee] }
CREATE TABLE public.implications (
	implicator INTEGER NOT NULL,
	implicatee INTEGER NOT NULL
);

ALTER TABLE public.implications ADD FOREIGN KEY (implicator) REFERENCES public.tags (id) ON DELETE RESTRICT;
ALTER TABLE public.implications ADD FOREIGN KEY (implicatee) REFERENCES public.tags (id) ON DELETE RESTRICT;





CREATE TABLE public.posts (
	id SERIAL PRIMARY KEY,
	file_hash CITEXT UNIQUE NOT NULL,
	pixel_hash CITEXT UNIQUE NOT NULL,
	width INTEGER NOT NULL,
	height INTEGER NOT NULL,
	status INTEGER NOT NULL DEFAULT 0,
	source TEXT,
	size INTEGER NOT NULL,
	file_type TEXT NOT NULL,
	favourite BOOLEAN NOT NULL DEFAULT false,
	favourited_at TIMESTAMP,
	version INTEGER NOT NULL DEFAULT 0,	-- Represents the latest version
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.post_history (
	id SERIAL PRIMARY KEY,
	post_id INTEGER NOT NULL,
	version INTEGER NOT NULL DEFAULT 0,
	created TIMESTAMP NOT NULL DEFAULT now()
	-- Revisions cannot be updated.
);





-- [akemi homura]:[punching]:[akemi homura]
-- [akemi homura]:[punching]:self
-- [tomoe mami]:[drinking]
-- [tomoe mami]:[drinking]:[tea]
-- INSERT INTO public.posts_tags (tag_id) VALUES (SELECT id FROM public.tags WHERE name = 'akemi homura');
-- See post #4819403
CREATE TABLE public.tags_history_pkx (
	actor_id INTEGER NOT NULL,	-- type must be Noun or Character
	verb_id INTEGER NOT NULL,	-- Type must be Verb
	target_id INTEGER,		-- Type must be Noun or Character
	version_id INTEGER NOT NULL
);

ALTER TABLE public.tags_history_pkx ADD FOREIGN KEY (actor_id) REFERENCES public.tags (id) ON DELETE RESTRICT;
ALTER TABLE public.tags_history_pkx ADD FOREIGN KEY (verb_id) REFERENCES public.tags (id) ON DELETE RESTRICT;
ALTER TABLE public.tags_history_pkx ADD FOREIGN KEY (target_id) REFERENCES public.tags (id) ON DELETE RESTRICT;
ALTER TABLE public.tags_history_pkx ADD FOREIGN KEY (version_id) REFERENCES public.post_history (id) ON DELETE RESTRICT;






CREATE TABLE public.commentary (
	id SERIAL PRIMARY KEY,
	language VARCHAR(3) NOT NULL,
	title TEXT,
	body TEXT,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.posts_commentary_pkx (
	post_id INTEGER NOT NULL,
	commentary_id INTEGER NOT NULL
);

ALTER TABLE public.posts_commentary_pkx ADD FOREIGN KEY (post_id) REFERENCES public.posts (id) ON DELETE RESTRICT;
ALTER TABLE public.posts_commentary_pkx ADD FOREIGN KEY (commentary_id) REFERENCES public.commentary (id) ON DELETE RESTRICT;





-- This is a part of tag logic.
-- #TODO: This requires more R&D.
CREATE TABLE public.sets (
	id SERIAL PRIMARY KEY,
	name TEXT UNIQUE NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.set_values (
	id SERIAL PRIMARY KEY,
	set_id INTEGER NOT NULL,
	value TEXT NOT NULL
);

ALTER TABLE public.set_values ADD FOREIGN KEY (set_id) REFERENCES public.sets (id) ON DELETE RESTRICT;





CREATE TABLE public.pools (
	id SERIAL PRIMARY KEY,
	name TEXT UNIQUE NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.posts_pools_pkx (
	post_id INTEGER NOT NULL,
	pool_id INTEGER NOT NULL
);

ALTER TABLE public.posts_pools_pkx ADD FOREIGN KEY (post_id) REFERENCES public.posts (id) ON DELETE RESTRICT;
ALTER TABLE public.posts_pools_pkx ADD FOREIGN KEY (pool_id) REFERENCES public.pools (id) ON DELETE RESTRICT;





-- Language codes are stored within the programme.
-- #TODO: Implement size and positioning logic (will need more columns)
CREATE TABLE public.translations (
	id SERIAL PRIMARY KEY,
	language INTEGER NOT NULL,
	data TEXT NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.posts_translations_pkx (
	post_id INTEGER NOT NULL,
	translation_id INTEGER NOT NULL
);

ALTER TABLE public.posts_translations_pkx ADD FOREIGN KEY (post_id) REFERENCES public.posts (id) ON DELETE RESTRICT;
ALTER TABLE public.posts_translations_pkx ADD FOREIGN KEY (translation_id) REFERENCES public.translations (id) ON DELETE RESTRICT;





CREATE TABLE public.artists (
	id SERIAL PRIMARY KEY,
	name TEXT UNIQUE NOT NULL,
	description TEXT,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.artists_urls (
	artist_id INTEGER NOT NULL,
	url TEXT UNIQUE NOT NULL
);

ALTER TABLE public.artists_urls ADD FOREIGN KEY (artist_id) REFERENCES public.artists (id) ON DELETE RESTRICT;





-- #NOTE: These are not unique to a given artist and will match any artist whom uses or has used a name in this table.
CREATE TABLE public.artist_aliases (
	id SERIAL PRIMARY KEY,
	name TEXT UNIQUE NOT NULL,
	created TIMESTAMP NOT NULL DEFAULT now()
	-- Revisions cannot be updated.
);





CREATE TABLE public.artist_aliases_pkx (
	artist_id INTEGER NOT NULL,
	alias_id INTEGER NOT NULL
);

ALTER TABLE public.artist_aliases_pkx ADD FOREIGN KEY (artist_id) REFERENCES public.artists (id) ON DELETE RESTRICT;
ALTER TABLE public.artist_aliases_pkx ADD FOREIGN KEY (alias_id) REFERENCES public.artist_aliases (id) ON DELETE RESTRICT;





CREATE TABLE public.artists_history_pkx (
	artist_id INTEGER NOT NULL,
	version_id INTEGER NOT NULL
);

ALTER TABLE public.artists_history_pkx ADD FOREIGN KEY (artist_id) REFERENCES public.artists (id) ON DELETE RESTRICT;
ALTER TABLE public.artists_history_pkx ADD FOREIGN KEY (version_id) REFERENCES public.post_history (id) ON DELETE RESTRICT;





CREATE TABLE public.circles (
	id SERIAL PRIMARY KEY,
	name TEXT UNIQUE NOT NULL,
	description TEXT,
	created TIMESTAMP NOT NULL DEFAULT now(),
	updated TIMESTAMP
);





CREATE TABLE public.artists_circles_pkx (
	artist_id INTEGER NOT NULL,
	circle_id INTEGER NOT NULL
);

ALTER TABLE public.artists_circles_pkx ADD FOREIGN KEY (artist_id) REFERENCES public.artists (id) ON DELETE RESTRICT;
ALTER TABLE public.artists_circles_pkx ADD FOREIGN KEY (circle_id) REFERENCES public.circles (id) ON DELETE RESTRICT;
