/*
 *  Copyright © 2017-2020 Wellington Wallace
 *
 *  This file is part of EasyEffects.
 *
 *  EasyEffects is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  EasyEffects is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with EasyEffects.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "echo_canceller_preset.hpp"

EchoCancellerPreset::EchoCancellerPreset()
    : input_settings(Gio::Settings::create("com.github.wwmm.easyeffects.echocanceller",
                                           "/com/github/wwmm/easyeffects/streaminputs/echocanceller/")),
      output_settings(Gio::Settings::create("com.github.wwmm.easyeffects.echocanceller",
                                            "/com/github/wwmm/easyeffects/streamoutputs/echocanceller/")) {}

void EchoCancellerPreset::save(boost::property_tree::ptree& root,
                               const std::string& section,
                               const Glib::RefPtr<Gio::Settings>& settings) {
  root.put(section + ".echo_canceller.input-gain", settings->get_double("input-gain"));

  root.put(section + ".echo_canceller.output-gain", settings->get_double("output-gain"));

  root.put(section + ".echo_canceller.frame-size", settings->get_int("frame-size"));

  root.put(section + ".echo_canceller.filter-length", settings->get_int("filter-length"));
}

void EchoCancellerPreset::load(const boost::property_tree::ptree& root,
                               const std::string& section,
                               const Glib::RefPtr<Gio::Settings>& settings) {
  update_key<double>(root, settings, "input-gain", section + ".echo_canceller.input-gain");

  update_key<double>(root, settings, "output-gain", section + ".echo_canceller.output-gain");

  update_key<int>(root, settings, "frame-size", section + ".echo_canceller.frame-size");

  update_key<int>(root, settings, "filter-length", section + ".echo_canceller.filter-length");
}

void EchoCancellerPreset::write(PresetType preset_type, boost::property_tree::ptree& root) {
  switch (preset_type) {
    case PresetType::output:
      save(root, "output", output_settings);
      break;
    case PresetType::input:
      save(root, "input", input_settings);
      break;
  }
}

void EchoCancellerPreset::read(PresetType preset_type, const boost::property_tree::ptree& root) {
  switch (preset_type) {
    case PresetType::output:
      load(root, "output", output_settings);
      break;
    case PresetType::input:
      load(root, "input", input_settings);
      break;
  }
}