all:
	@echo Run container with: \`docker-compose run --rm --workdir=/src dev-env\'

run:
	docker-compose run --rm --workdir=/src dev-env
