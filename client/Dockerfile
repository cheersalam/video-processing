

FROM node:alpine as build


WORKDIR /app
COPY package*.json ./
RUN npm install 
COPY . .
RUN npm run build

FROM nginx 

# replace with custom one
#COPY nginx/nginx.conf /etc/nginx/
#COPY nginx/nginx.conf /etc/nginx/conf.d

EXPOSE 80
EXPOSE 3000
COPY --from=build /app/build /usr/share/nginx/html