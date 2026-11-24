FROM node

ENV MONGO_DB_USERNAME=admin \
    MONGO_DB_PWD=password

RUN mkdir -p test-app

COPY . /test-app

CMD ["node", "/test-app/server.js"]