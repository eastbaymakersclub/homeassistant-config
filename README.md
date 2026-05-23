# Home Assistant Config

Home Assistant configuration for East Bay Makers Club.

This repository tracks the hand-authored Home Assistant and ESPHome source files. Secrets, recorder databases, logs, caches, media, backups, and generated ESPHome build output are intentionally ignored.

To refresh the checked-in Home Assistant files from the running host:

```sh
rsync -av \
  --exclude='.git/' \
  --exclude='.DS_Store' \
  --exclude='.cloud/' \
  --exclude='.storage/' \
  --exclude='.cache/' \
  --exclude='.ha_run.lock' \
  --exclude='deps/' \
  --exclude='tts/' \
  --exclude='image/' \
  --exclude='media/' \
  --exclude='backups/' \
  --exclude='*.db' \
  --exclude='*.db-*' \
  --exclude='*.log' \
  --exclude='*.log.*' \
  --exclude='*.lock' \
  --exclude='secrets.yaml' \
  --exclude='**/__pycache__/' \
  --exclude='*.pyc' \
  --exclude='custom_components/hacs/' \
  --exclude='esphome/' \
  root@homeassistant.localdomain:/config/ ./
```

ESPHome configs are kept locally in `esphome/`; generated builds live under `esphome/.esphome/` and are not committed.
