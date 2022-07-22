FROM alpine:latest
RUN apk update && apk add python3 py3-pip git make gcc libc-dev sed

RUN adduser -D user
USER user
WORKDIR /home/user

RUN pip3 install wolframalpha sympy
ENV PATH="/home/user/.local/bin:${PATH}"

COPY --chown=user:user . .

CMD git clone https://github.com/Maxmosk/The-quadratic-equation.git --depth 1 && cd The-quadratic-equation && sed -i 's/$(CFLAGS_FLAGS)/ /' Makefile && sed -i 's/$(CFLAGS_LINK)/ /' Makefile && make && ./tests/quadtests.sh ./build/quad && ./tests/quadtests.py && exit

