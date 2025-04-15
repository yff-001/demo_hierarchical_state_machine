#!/bin/bash

set -e  # Exit on first error

echo "🔨 Building firmware..."
make all

echo ""
echo "🧪 Running unit tests..."
make test

echo ""
echo "✅ Build and test complete."
