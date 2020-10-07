FROM openjdk:12	

WORKDIR /

ADD build/libs/HTTP_Server-0.0.1.jar ChatServer.jar

ADD resources/ resources/

Expose 8080

CMD java -jar ChatServer.jar