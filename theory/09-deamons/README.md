# Тема 9. Демони и systemd

Съдържание:


1. TL;DR
2. Какво е daemon (демон)
3. Background process vs Daemon
4. PID 1 и init системата
5. systemd
6. systemctl
7. journalctl
8. Systemd unit files
9. Lifecycle на service
10. Полезни команди
11. Демонстрации



# 1. TL;DR

TL;DR: Демоните са процеси, които работят постоянно във background-а и предоставят услуги на системата или други програми.

Примери:

* web server
* ssh server
* database
* docker daemon

В модерните Linux системи те се управляват чрез:

```bash
systemd
```

и:

```bash
systemctl
```

# 2. Какво е daemon (демон)

Daemon е специален тип процес, който:

* работи във background-а
* няма нужда от terminal
* обикновено работи постоянно
* чака заявки/събития
* предоставя услуга

Може да мислим за daemon като:

> “невидим системен работник”.

Примери:

* `sshd` → приема SSH връзки
* `nginx` → web server
* `dockerd` → Docker daemon
* `cron` → scheduler
* `systemd-journald` → logging daemon

# 3. Background process vs Daemon

Важно:
Не всеки background process е daemon.

Пример:

```bash
./app &
```

Това стартира процес във background-а, но:

* той още е свързан към shell-а
* може да умре при logout
* не е истински system service

Истинският daemon:

* се detach-ва от terminal-а
* няма controlling terminal
* често се стартира от PID 1
* работи независимо

# 4. PID 1 и init системата

В Linux първият процес е:

```bash
PID 1
```

Това е init системата.

Нейната задача е:

* да стартира останалите services
* да следи системата
* да рестартира crash-нали процеси
* да управлява boot процеса

В модерните Linux системи PID 1 обикновено е:

systemd

# 5. systemd

systemd е:

* init система
* service manager
* logging system
* boot manager

Той управлява:

* services
* mounts
* sockets
* timers
* targets

Проверка:

```bash
ps -p 1
```

Ще видите process-а с PID 1.

# 6. systemctl

Основният инструмент за управление е:

```bash
systemctl
```

## Най-важни команди

### Стартиране

```bash
sudo systemctl start nginx
```

### Спиране

```bash
sudo systemctl stop nginx
```

### Рестарт

```bash
sudo systemctl restart nginx
```

### Статус

```bash
systemctl status nginx
```

### Auto-start при boot

```bash
sudo systemctl enable nginx
```

### Спиране на auto-start

```bash
sudo systemctl disable nginx
```

## Важно

* `start/stop`
  → сега

* `enable/disable`
  → при boot

Това е една от най-честите грешки при начинаещи.

# 7. journalctl

`journalctl` се използва за четене на system logs.

Най-лесният начин да се запомни:

> systemctl управлява services
> journalctl чете какво са казали

## Примери

### Логове на конкретен service

```bash
journalctl -u nginx
```

### Последни errors

```bash
journalctl -xe
```

### Live logs

```bash
journalctl -f
```

Работи подобно на:

```bash
tail -f
```

### Последните 20 лога

```bash
journalctl -u nginx -n 20
```

# 8. Systemd unit files

Services се описват чрез:

```bash
*.service
```

файлове.

Най-често се намират в:

```bash
/etc/systemd/system/
```

или:

```bash
/lib/systemd/system/
```

Пример:

```ini
[Unit]
Description=My App
After=network.target

[Service]
ExecStart=/opt/myapp/app
Restart=always
User=www-data

[Install]
WantedBy=multi-user.target
```

# 9. Lifecycle на service

## [Unit]

Обща информация и dependencies.

Примери:

* Description
* After
* Requires



## [Service]

Как се стартира процесът.

Най-важната секция.

Примери:

* ExecStart
* Restart
* User
* WorkingDirectory
* Environment



## [Install]

Как service-ът участва в boot процеса.

Най-често:

```ini
WantedBy=multi-user.target
```



# 10. Полезни команди

## Reload на конфигурациите

```bash
sudo systemctl daemon-reload
```

Казва на systemd:
“прочети наново service файловете”.



## Всички services

```bash
systemctl list-units --type=service
```



## Само failed services

```bash
systemctl --failed
```



## Проверка дали service е active

```bash
systemctl is-active nginx
```

---

# 11. Демонстрации

## Създаване на собствен service

### 1. Създаваме unit file

```bash
sudo nano /etc/systemd/system/myapp.service
```

### 2. Reload

```bash
sudo systemctl daemon-reload
```

### 3. Enable

```bash
sudo systemctl enable myapp
```

### 4. Start

```bash
sudo systemctl start myapp
```

### 5. Проверка

```bash
systemctl status myapp
```

### 6. Логове

```bash
journalctl -u myapp
```
